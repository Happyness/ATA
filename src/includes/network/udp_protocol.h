#ifndef _UDP_PROTOCOL_H
#define _UDP_PROTOCOL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#if defined(__WIN32__) || defined(WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <inttypes.h>
#define CLOSE closesocket
#else
#define CLOSE close
#include <sys/select.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netdb.h>
#endif

// Defines for handshake packet flags
#define SYN 1
#define ACK 2
#define RST 4
#define RST_ACK 8

// Defines for packet_to_string() function
#define HANDSHAKE 0
#define DATA 1

// Defines for connection_termination() function
#define SERVER 0
#define CLIENT 1

/*
  Author: Sofia and Daniel
  Description: Packet type that will be used for actual data transfers
  Param: proto_id is always "herp", trailer is always "derp".
 */
typedef struct {
  char *proto_id;
  uint8_t packet_type;
  uint32_t seq_nr;
  uint32_t ack;
  uint32_t ack_seq;
  uint32_t client_id;
  void *data;
  char *trailer;
} data_packet;

/*
  Author: Sofia and Daniel
  Description: Packet type that will be used for initial handshake and
  teardown of the connection.
  Param: proto_id is always "herp", trailer is always "derp".
  flags are defined as SYN = 1, ACK = 2, RST = 4, RST_ACK = 8
 */
typedef struct {
  char *proto_id;
  uint8_t packet_type;
  char *client_ip;
  uint16_t client_port;
  uint32_t client_id;
  uint8_t flags;
  char *trailer;
} handshake_packet;

/*
  Author: Sofia and Daniel
  Description: Datatype for connection related data, like sending and
  receiving end and assigned socket.
 */
typedef struct {
  struct sockaddr_in *destination;
  int sock_fd;
  uint32_t client_id;
  char *client_ip;
  uint16_t client_port;
} connection_data;

int connect_session(connection_data *, char *, uint16_t, char *);
int end_session(connection_data *);
int send_data(connection_data *, char *);
int accept_session(connection_data *, uint16_t, int);
int net_init(void);
int net_cleanup(void);
int is_packet(void *, uint32_t);
int connection_termination(connection_data *, uint8_t);
void *string_to_packet(char *, uint32_t);
void *recv_data(connection_data *);
char *packet_to_string(void *, uint32_t);
char *listen_socket (connection_data *);
connection_data *create_connection_data(char *, uint16_t, uint32_t, uint32_t, connection_data *);
int setNonblockMode(uint32_t s);
#endif
