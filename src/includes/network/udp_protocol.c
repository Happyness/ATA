#ifndef _UDP_PROTOCOL_C
#define _UDP_PROTOCOL_C

#include "udp_protocol.h"

#if defined(__WIN32__) || defined(WIN32)
/*
 *  Author: Daniel
 *  Description: Reimplementation of strsep for windows, as it doesn't have it in it's string.h, based on the description
 *  of the function in the manpage
 *  Params: char **stringp, a pointer to a string, that will be repositioned while the string is parsed
 *  const char *delim, a string that contains the delimiter that the inputted string will be split at
 *  Return value: The function will return NULL if the pointer to a string is NULL, else the part of the string
 */
char *strsep(char **stringp, const char *delim) 
{
	char *start = *stringp;
	char *p = NULL;
	
	p = (start != NULL) ? strpbrk(start, delim) : NULL;
	
	if (p == NULL)  
	{
		*stringp = NULL;
	} 
	else 
	{
		*p = '\0';
		*stringp = p + 1;
	}
	
	return start;
}
#endif


/*
 *  Author: Daniel and Sofia
 *  Description: Function that initializes the connection between client and server
 *  Params: connection_data *connection, used to fill in the address and socket information
 *  to be used in subsequent send_data() calls.
 *  char *server_ip, a string with the server IP address to connect to
 *  uint16_t server_port, a unsigned 2 byte long integer with the server port to connect to
 *  char *client_ip, a string with the client IP address
 *  int client_id, the identification of the client
 *  Return value: returns 0 if successful, -1 on failure and a error message is written to stderr
 */
int connect_session(connection_data *connection, char *server_ip, uint16_t server_port, char *client_ip) 
{
	handshake_packet syn_packet, *received_packet = NULL;
	fd_set listen_set;
	int i = 0, return_value = 0;
	char *ptr = NULL;
	uint32_t sock_fd = 0;
	struct timeval timeout;
	
	srand(time(NULL));
	
	net_init();
	FD_ZERO(&listen_set);
	
	printf("Before creating socket.\n");
	if ((sock_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) 
	{
		perror("socket() failed");
		return -1;
	}
	printf("After creating socket.\n");
	
	printf("Preparing SYN packet.\n"); 
	syn_packet.proto_id = "herp";
	syn_packet.packet_type = HANDSHAKE;
	syn_packet.client_ip = client_ip;
	syn_packet.client_port = 1026;
	syn_packet.client_id = rand();
	syn_packet.flags = SYN;
	syn_packet.trailer = "derp";
	
	printf("Converting to string.\n");
	ptr = packet_to_string(&syn_packet, HANDSHAKE);
	
	printf("Setting up listening socket.\n");
	
	connection = create_connection_data(client_ip, 1026, syn_packet.client_id, sock_fd, connection);
	
	printf("Binding socket.\n");
	if (bind(connection->sock_fd, (struct sockaddr *)connection->destination, sizeof(struct sockaddr)) < 0) 
	{
		perror("Bind() failed");
		CLOSE(connection->sock_fd);
		return -1;
	}
	
	printf("Creating connection_data.\n");
	connection = create_connection_data(server_ip, server_port, syn_packet.client_id, connection->sock_fd, connection);
	for(i = 0; i < 3; i++) 
	{
		printf("Try %d\n", i+1);
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		FD_SET(sock_fd, &listen_set);
		
		printf("Sending data, %d bytes timeout: %d s %d us.\n", strlen(ptr), timeout.tv_sec, timeout.tv_usec);
		printf("Struct data: %d %d %d socket: %d client_id: %d\n", connection->destination->sin_family, connection->destination->sin_port, connection->destination->sin_addr.s_addr, connection->sock_fd, connection->client_id);
		
		if (sendto(connection->sock_fd, ptr, strlen(ptr), 0, (struct sockaddr *)connection->destination, sizeof(struct sockaddr)) < 0) 
		{
			perror("sendto() failed");
			CLOSE(connection->sock_fd);
			return -1;
		}
		
		printf("Entering listening mode.\n");
		while(1) 
		{
			if (FD_ISSET(connection->sock_fd, &listen_set))
			{
				return_value = select(connection->sock_fd+1, &listen_set, NULL, NULL, &timeout);
				printf("Return_value: %d\n", return_value);
			} 
			else 
			{
				fprintf(stderr, "FD_SET was never called on the socket %d, quitting connection attempt.\n", connection->sock_fd);
				return -1;
			}
			
			if (return_value == -1) 
			{
				perror("Select() failed");
			CLOSE(connection->sock_fd);
			return -1;
			} 
			else if (return_value) 
			{
				ptr = listen_socket(connection);
				printf("Received string: %s\n", ptr);
	
	if (atoi(&ptr[5]) == HANDSHAKE) 
	{
		printf("It is a handshake packet outside recv_data!\n");
		received_packet = (handshake_packet *)string_to_packet(ptr, HANDSHAKE);
		printf("ptr size %d\n", strlen(ptr));
		
		if (!is_packet(received_packet, HANDSHAKE) && !strncmp(connection->client_ip, received_packet->client_ip, strlen(connection->client_ip)) && (received_packet->flags == ACK)) 
		{
			printf("ACK packet received: %p.\n", connection);
			connection->client_id = received_packet->client_id;
			return 0;
			
		}
	} 
	else 
	{
		printf("Is not a packet :(\n");
		break;
	}
			} 
			else 
			{
				printf("No ACK received within 5 seconds, retrying %d times more.\n", 3-(i+1));
		break;
			}
		}
	}
	
	fprintf(stderr, "The server never responded, please try again later.\n");
	return -1;
}

/*
 *  Author: Sofia and Daniel
 *  Description: Function that accept a request from a client to start a connection with the server.
 *  Params: connection_data *connection, used to fill in the address and socket information of the client
 *  to be used in subsequent send_data() calls to the client.
 *  uint32_t port, a unsigned 4 byte long integer with the port to listen on
 *  int client_id, integer value that contains the client_id to assign to the client
 *  Return value: returns 0 if successful, -1 if failure and a error message is written to stderr.
 */
int accept_session (connection_data *connection, uint16_t port, int client_id) 
{
	handshake_packet ack_packet, *received_packet = NULL;
	static first_time = 1;
	static uint32_t sock_fd;
	char *ptr = NULL;
	
	printf("Sock_fd in the beginning: %d\n", sock_fd);
	
	if (first_time) 
	{
		net_init();
		
		printf("Before creating socket.\n");
		if ((sock_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) 
		{
			perror("socket() failed");
			return -1;
		}
		printf("After creating socket.\n");
	}
	
	connection = create_connection_data("0.0.0.0", port, 0, sock_fd, connection);
	
	if (first_time) 
	{
		printf("Setting up listening socket.\n");
		
		printf("Binding socket.\n");
		if (bind(sock_fd, (struct sockaddr *)connection->destination, sizeof(struct sockaddr)) < 0) 
		{
			perror("Bind() failed");
			CLOSE(sock_fd);
			return -1;
		}
		
		first_time = 0;
	}
	
	while(1) 
	{
		printf("Listening for SYN packet.\n");
		printf("connection->sock_fd: %d\n", connection->sock_fd);
		ptr = listen_socket(connection);
		
		if (atoi(&ptr[5]) == HANDSHAKE) 
		{
			printf("Converting from string to packet.\n");
			received_packet = (handshake_packet *)string_to_packet (ptr, HANDSHAKE);
			printf("ptr size %d\n", strlen(ptr));
			
			printf("It is a handshake packet outside recv_data!\n");
			printf("Content: %s %u %s %u %u %s\n", received_packet->proto_id, received_packet->packet_type, received_packet->client_ip, received_packet->client_port, received_packet->flags, received_packet->trailer);
			if (!is_packet(received_packet, HANDSHAKE) && received_packet->flags == SYN) 
			{
				printf("SYN Packet received.\n");
			break;
			}
		}
	}
	
	printf("Preparing ACK packet.\n");
	ack_packet.proto_id = "herp";
	ack_packet.packet_type = HANDSHAKE;
	ack_packet.client_ip = received_packet->client_ip;
	ack_packet.client_id = client_id;
	ack_packet.flags = ACK;
	ack_packet.trailer = "derp";
	
	printf("Creating connection_data struct.\n");
	connection = create_connection_data(received_packet->client_ip, received_packet->client_port, client_id, connection->sock_fd, connection);
	
	printf("Converting packet_to_string.\n");
	ptr = packet_to_string(&ack_packet, HANDSHAKE);
	
	free(received_packet);
	
	printf("Sending ACK packet.\n");
	if (sendto(connection->sock_fd, ptr, strlen(ptr), 0, (struct sockaddr *)connection->destination, sizeof(struct sockaddr)) < 0) 
	{
		perror("sendto() failed");
		CLOSE(connection->sock_fd);
		return -1;
	}
	
	printf("pointer address %p\n", connection);
	
	return 0;
}

/*
 *  Author: Daniel
 *  Description: Function to terminate a active session
 *  Params: connection_data *connection, struct containing the connection details
 *  Return value: returns 0 if successful and -1 if failed and a error message is printed to stderr
 */
int end_session(connection_data *connection) 
{
	handshake_packet rst_packet, *received_packet = NULL;
	char *ptr = NULL;
	
	rst_packet.proto_id = "herp";
	rst_packet.packet_type = HANDSHAKE;
	rst_packet.client_ip = connection->client_ip;
	rst_packet.client_port = connection->client_port;
	rst_packet.client_id = connection->client_id;
	rst_packet.flags = RST;
	rst_packet.trailer = "derp";
	
	ptr = packet_to_string(&rst_packet, HANDSHAKE);
	
	if (sendto(connection->sock_fd, ptr, strlen(ptr), 0, (struct sockaddr *)connection->destination, sizeof(struct sockaddr)) < 0) 
	{
		perror("sendto() failed");
		CLOSE(connection->sock_fd);
		return -1;
	}
	
	while(1) 
	{
		printf("Listening for RST_ACK packet.\n");
		ptr = listen_socket(connection);
		
		printf("ptr size %d\n", strlen(ptr));
		printf("packet type: %d ptr: %s\n", atoi(&ptr[5]), ptr);
		if (atoi(&ptr[5]) == HANDSHAKE) 
		{
			printf("Converting from string to packet.\n");
			received_packet = (handshake_packet *)string_to_packet (ptr, atoi(&ptr[5]));
			
			printf("It is a handshake packet outside recv_data()!\n");
			if (!is_packet(received_packet, HANDSHAKE) && (received_packet->flags == RST_ACK)) 
			{
				printf("RST_ACK Packet received.\n");
			connection_termination(connection, CLIENT);
			free(received_packet);
			return 0;
			} 
			else 
			{
				free(received_packet);
			}
		}
	}
	
	fprintf(stderr, "You should never run this code.\n");
	return -1;
}

/*
 *   Author: Daniel
 *   Description: Function that converts a packet struct into a string for sending over the wire.
 *   Params: void *packet, a pointer to whichever packet struct.
 *   uint32_t type, gives the type of packet (DATA or HANDSHAKE) to know how to prepare the string.
 *   Return value: returns a pointer to the resulting string and NULL on failure
 */
char *packet_to_string(void *packet, uint32_t type) 
{
	char *ptr = NULL;
	handshake_packet *hs_ptr = NULL;
	data_packet *data_ptr = NULL;
	printf("Inside packet_to_string.\n");
	switch(type) 
	{
		case 0:
			printf("Inside handshake case.\n");
			ptr = malloc(sizeof(char) * 64);
			hs_ptr = (handshake_packet *)packet;
			snprintf(ptr, 64, "%s %u %s %u %u %u %s", hs_ptr->proto_id, hs_ptr->packet_type, hs_ptr->client_ip, hs_ptr->client_port, hs_ptr->client_id, hs_ptr->flags, hs_ptr->trailer);
			printf("%s %u %s %u %u %u %s\n", hs_ptr->proto_id, hs_ptr->packet_type, hs_ptr->client_ip, hs_ptr->client_port, hs_ptr->client_id, hs_ptr->flags, hs_ptr->trailer, ptr);
			break;
		case 1:
			printf("Inside data case.\n");
			ptr = malloc(sizeof(char) * 1500);
			data_ptr = (data_packet *)packet;
			snprintf(ptr, 1500, "%s %u %u %u %u %u %s %s", data_ptr->proto_id, data_ptr->packet_type, data_ptr->seq_nr, data_ptr->ack, data_ptr->ack_seq, data_ptr->client_id, (char *)data_ptr->data, data_ptr->trailer);
			printf("%s %u %u %u %u %u %s %s\n%s\n", data_ptr->proto_id, data_ptr->packet_type, data_ptr->seq_nr, data_ptr->ack, data_ptr->ack_seq, data_ptr->client_id, (char *)data_ptr->data, data_ptr->trailer, ptr);
			break;
	}
	
	return ptr;
}

/*
 * Author: Sofia and Daniel
 * Description: Function that listen for packets
 * Params: connection_data *connection to reach information in sock_fd.
 * Return value: a string containing the received packet
 */
char *listen_socket (connection_data *connection) 
{
	char *ptr = malloc(sizeof(char) * 1500);
	socklen_t socklen = sizeof(struct sockaddr);
	
	printf("Before recvfrom() in listen socket.\n");
	if (recvfrom(connection->sock_fd, ptr, 1500, 0, (struct sockaddr *)connection->destination, &socklen) < 0) 
	{
		perror ("recvfrom() failed");
		return NULL;
	}
	
	printf("After recvfrom().\n");
	return ptr;
}

/*
 *   Author: Daniel
 *   Description: Function that converts a received string to a packet struct.
 *   Params: char *string, received string
 *   uint32_t type, the type of packet (DATA or HANDSHAKE), so it knows what packet format to use
 *   Return value: returns a pointer to the resulting string and NULL on failure
 */
void *string_to_packet(char *string, uint32_t type) 
{
	handshake_packet *hs_ptr = NULL;
	data_packet *data_ptr = NULL;
	void *ptr = NULL;
	int i;
	
	printf("Inside string_to_packet.\n");
	switch(type) 
	{
		case 0:
			printf("Inside handshake case %s.\n", string);
			hs_ptr = malloc(sizeof(handshake_packet));
			for(i = 0; i < 7; i++) 
			{
				switch(i) 
				{
					case 0:
						hs_ptr->proto_id = strsep(&string, " "); break;
					case 1:
						hs_ptr->packet_type = atoi(strsep(&string, " ")); break;
					case 2:
						hs_ptr->client_ip = strsep(&string, " "); break;
					case 3:
						hs_ptr->client_port = atoi(strsep(&string, " ")); break;
					case 4:
						hs_ptr->client_id = atoi(strsep(&string, " ")); break;
					case 5:
						hs_ptr->flags = atoi(strsep(&string, " ")); break;
					case 6:
						hs_ptr->trailer = strsep(&string, " "); break;
				}
			}
			printf("Packet: %s %u %u %s\n", hs_ptr->proto_id, hs_ptr->client_id, hs_ptr->flags, hs_ptr->trailer);
			ptr = (void *)hs_ptr;
			break;
					case 1:
						printf("Inside data case %s.\n", string);
	data_ptr = malloc(sizeof(data_packet));
	for(i = 0; i < 8; i++) 
	{
		switch(i) 
		{
			case 0:
				data_ptr->proto_id = strsep(&string, " "); break;
			case 1:
				data_ptr->packet_type = atoi(strsep(&string, " ")); break;
			case 2:
				data_ptr->seq_nr = atoi(strsep(&string, " ")); break;
			case 3:
				data_ptr->ack = atoi(strsep(&string, " ")); break;
			case 4:
				data_ptr->ack_seq = atoi(strsep(&string, " ")); break;
			case 5:
				data_ptr->client_id = atoi(strsep(&string, " ")); break;
			case 6:
				data_ptr->data = (void *)strsep(&string, " "); break;
			case 7:
				data_ptr->trailer = strsep(&string, " "); break;
		}
	}
	ptr = (void *)data_ptr;
	break;
	}
	free(string);
	
	return ptr;
}

/*
 *   Author: Daniel
 *   Description: Function that creates socket and sockaddr_in struct that composes a connection_data variable
 *   Params: char *ip, a string with the IP to connect to
 *   uint16_t port, a 2 byte unsigned int with the port to connect to
 *   uint32_t client_id, the client id to assign in the connection_data struct
 *   uint32_t sock_fd, the associated socket that is to be used for listening/sending packets for this connection
 *   connection_data *connection, a pointer to the connection_data struct that the information should be put into
 *   Return value: if successful a pointer to the resulting connection_data struct is returned, else NULL
 */
connection_data *create_connection_data(char *ip, uint16_t port, uint32_t client_id, uint32_t sock_fd, connection_data *connection) 
{
	struct sockaddr_in *destination = malloc(sizeof(struct sockaddr_in));
	
	printf("pointer: %p\n", connection);
	
	destination->sin_addr.s_addr = inet_addr(ip);
	destination->sin_port = htons(port);
	destination->sin_family = AF_INET;
	printf("Before assigning to connection_data struct.\n");
	printf("Struct data: %d %d %d\n", destination->sin_family, destination->sin_port, destination->sin_addr.s_addr);
	connection->destination = destination;
	printf("Struct data: %d %d %d\n", connection->destination->sin_family, connection->destination->sin_port, connection->destination->sin_addr.s_addr);
	connection->sock_fd = sock_fd;
	connection->client_id = client_id;
	connection->client_ip = ip;
	connection->client_port = port;
	printf("After assigning to connection_data struct.\n");
	
	return connection;
}

/*
 * Author: Daniel
 * Description: Net initialization function only needed in windows environment
 * Params: void
 * Return value: returns 0 on success, -1 on failure, will always return 0 on non-windows platforms
 */
int net_init(void)
{
	#if defined(__WIN32__) || defined(WIN32)
	WORD version_wanted = MAKEWORD(1,1);
	WSADATA wsa_data;
	
	if (WSAStartup(version_wanted, &wsa_data) != 0) 
	{
		printf("WSAStartup() failed: %d\n", WSAGetLastError());
		return -1;
	} 
	else 
	{
		return 0;
	}
	#else
	return 0;
	#endif
}

/*
 * Author: Daniel
 * Description: Net cleanup function only needed in windows environment
 * Params: void
 * Return value: returns 0 on success, -1 on failure, will always return 0 on non-windows platforms
 */
int net_cleanup(void) 
{
	#if defined(__WIN32__) || defined(WIN32)
	if ( WSACleanup() == SOCKET_ERROR ) 
	{
		if ( WSAGetLastError() == WSAEINPROGRESS ) 
		{
			WSACancelBlockingCall();
			WSACleanup();
			return 0;
		}
	}
	return 0;
	#else
	return 0;
	#endif
}
#endif

/*
 * Author: Sofia and Daniel
 * Description: A function to send a string inside a data packet 
 * Params: connection_data *connection, a struct containing relevant socket information
 * char *data, the string to be sent
 * Return value: The function will return 0 if success, and -1 if failed.
 */
int send_data (connection_data *connection, char *data) 
{
	data_packet d_packet;
	char *ptr = malloc(sizeof(char) * 1500);
	static uint32_t sequence_nr;
	
	d_packet.proto_id = "herp";
	d_packet.packet_type = DATA;
	d_packet.seq_nr = sequence_nr;
	d_packet.ack = 0;
	d_packet.ack_seq = 0;
	d_packet.client_id = connection->client_id;
	d_packet.data = (void *)data;
	d_packet.trailer = "derp";
	
	ptr = packet_to_string(&d_packet, DATA);
	
	if (sendto(connection->sock_fd, ptr, strlen(ptr)+1, 0, (struct sockaddr *)connection->destination, sizeof(struct sockaddr)) <0) 
	{
		perror ("sendto (func send_data) failed!");
		return -1;
	}
	
	sequence_nr++;
	return 0;
}

/*
 * Author: Sofia and Daniel
 * Description: A function to receive data packets
 * Params: connection_data *connection, a struct containing relevant socket information
 * Return value: The function will return the data in the received packet if success, NULL if failed and 
 * "Connection terminated." if a RST is received.
 */
void *recv_data (connection_data *connection) 
{
	char *ptr = malloc (sizeof (char) * 1500 );
	data_packet *data_ptr = NULL;
	handshake_packet *hs_ptr = NULL;
	fd_set listen_set;
	struct timeval timeout;
	int result;
	
	FD_ZERO(&listen_set);
	FD_SET(connection->sock_fd, &listen_set);
	
	if (FD_ISSET(connection->sock_fd, &listen_set))
	{
		timeout.tv_sec = 60;
		timeout.tv_usec = 0;
		
		result = select(connection->sock_fd+1, &listen_set, NULL, NULL, &timeout);
	} else {    
		fprintf(stderr, "FD_SET was never called on the socket %d, quitting attempt.\n", connection->sock_fd);
		return NULL;
	}
	
	if (result == -1) {
		perror("Select() failed");
		return NULL;
	} else if (result) {
		printf("Listen socket in recv-data\n");
		ptr = listen_socket(connection);
		
		switch(atoi(&ptr[5])) 
		{
			case 0:
				hs_ptr = string_to_packet(ptr, HANDSHAKE);
				
				if (!is_packet(hs_ptr, HANDSHAKE) && (connection->client_id == 0 || connection->client_id == hs_ptr->client_id)) 
				{
					printf("It is a handshake packet!\n");
					
					if (hs_ptr->flags != RST) {
						return NULL;
					} else	{
						connection_termination(connection, SERVER);
						return "Terminated";
					}
				} else 
{
					printf("Is not a packet :(\n");
					return NULL;
				}
				break;
			case 1:
				data_ptr = string_to_packet (ptr, DATA);
				
				if (!is_packet(data_ptr, DATA)) {
					printf("Data packet received, containing data: %s\n", (char *)data_ptr->data);
					return data_ptr->data;
				} else {
					return NULL;
				}
				break;
			default:
				return NULL; break;
		}
	} else {
		fprintf(stderr, "No packet received within timeout period, exiting...\n");
		return NULL;  
	}
}

/*
 * Author: Daniel
 * Description: A function to validate if a received packet is a correct packet
 * Params: void *packet_ptr, pointer to the packet to be validated
 * uint32_t type, type of packet to validate 
 * Return value: returns 0 if valid, 1 if not
 */
int is_packet(void *packet_ptr, uint32_t type) 
{
	handshake_packet *hs_ptr = NULL;
	data_packet *data_ptr = NULL;
	
	printf("In is_packet, before switch: %d\n", type);
	
	switch(type) 
	{
		case 0:
			printf("is handshake?\n");
			hs_ptr = (handshake_packet *)packet_ptr;
			if (!strncmp("herp", hs_ptr->proto_id, 4) && !strncmp("derp", hs_ptr->trailer, 4)) 
			{
				printf("Is a handshake!\n");
				return 0;
			} 
			else 
			{
				printf("Is not a handshake :(\n");
				return 1;
			}
			break;
		case 1:
			printf("is data?\n");
			data_ptr = (data_packet *)packet_ptr;
			if (!strncmp("herp", data_ptr->proto_id, 4) && !strncmp("derp", data_ptr->trailer, 4)) 
			{
				printf("Is a data\n");
				return 0;
			} 
			else 
			{
				printf("Is not a data :(\n");
				return 1;
			}
	}
}

/*
 *  Author: Daniel
 *  Description: A function to terminate a connection entirely
 *  Params: connection_data *connection, struct containing the data for the session to terminate
 *  uint8_t side, value that contains CLIENT or SERVER
 *  Return value: returns 0 on success.
 */
int connection_termination(connection_data *connection, uint8_t side) 
{
	handshake_packet *rst_ack_packet = NULL;
	char *ptr = NULL;
	printf("Terminating connection.\n");
	
	switch(side) 
	{
		case 0:
			printf("Preparing RST_ACK packet.\n");
			rst_ack_packet = malloc(sizeof(handshake_packet));
			rst_ack_packet->proto_id = "herp";
			rst_ack_packet->packet_type = HANDSHAKE;
			rst_ack_packet->client_ip = connection->client_ip;
			rst_ack_packet->client_port = connection->client_port;
			rst_ack_packet->client_id = connection->client_id;
			rst_ack_packet->flags = RST_ACK;
			rst_ack_packet->trailer = "derp";
			
			ptr = malloc(sizeof(char) * 64);
			
			printf("Converting to string.\n");
			ptr = packet_to_string(rst_ack_packet, HANDSHAKE);
			
			printf("Sending RST_ACK.\n");
			if (sendto(connection->sock_fd, ptr, strlen(ptr), 0, (struct sockaddr *)connection->destination, sizeof(struct sockaddr)) < 0) 
			{
				perror("sendto() failed in RST_ACK");
				CLOSE(connection->sock_fd);
				return -1;
			}
			
			printf("Closing socket.\n");
			CLOSE(connection->sock_fd);
			printf("Freeing connection_data.\n");
			free(connection);
			
			break;
		case 1:
			printf("Closing socket.\n");
			CLOSE(connection->sock_fd);
			printf("Freeing connection_data.\n");
			free(connection);
			
			break;
	}
	net_cleanup();
	return 0;
}
