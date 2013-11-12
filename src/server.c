/*
 Author: 	Joel Denke and Marcus Isaksson
 Description: 	Runs the server with SDL threads for each client connection
 Created:	12 april 2012
 */

// System headers
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL_thread.h>
#include <SDL_mutex.h>
#include <SDL.h>

// User headers
#include "includes/graphics/structure.h"
#include "includes/player/controller.h"
#include "includes/libcalc.h"
#include "includes/linkedList.h"
#include "includes/network/udp_protocol.h"

#define LOG "./eventhandling.log"
#define SIZE 4096
#define PORT 1025

int runPlayer(void* parameters);
void _logit(FILE *, char *);

int noClients = 6;
char** messageBuffer;

SDL_Thread *threads[NO_PLAYERS];
SDL_Thread *listener;
SDL_mutex  *lock;
world gameWorld;

typedef struct {
	int available, team;
	connection_data * data;
} client;

typedef struct {
	void * function;
} eCallback;

typedef enum {gPause, gRunning, gEnd} gState;
client clients[NO_PLAYERS];
int teams[NO_TEAMS];
gState state;

void sendToClient(player * player)
{
	// string_to_packet();
}

int clientDisconnect(int i)
{
	//int id = clients[i].id;
	connection_data *connection = clients[i].data;

	return end_session(connection);
}

int isConnected(int id)
{
	return 1;
}

int hasInput()
{
	return 1;
}

/*
 Author: 	Joel Denke
 Description: 	Get first available team number.
 Params: 	id		Team number choice of player
 Return value:  Returns -1:( > 0) depending if team available or not.
 */
int getAvailableTeam(int choice)
{
	int i;
	int players = (NO_PLAYERS / NO_TEAMS);

	if (teams[choice] < players) {
		teams[choice]++;

		return choice;
	} else {
		for (i = 0; i < NO_TEAMS; i++) {
			if (teams[i] < players) {
				teams[i]++;

				return i;
			}
		}
	}

	return -1;
}

/*
 Author: 	Joel Denke
 Description: 	Initiates a player on a thread.
 Params: 	id	Client identification number
 Return value:  Returns 0:1 depending if thread creation is succeeded or not.
 */
int initPlayer(int i)
{
	int rValue;
	player player;

	gameWorld.players[i]            = player;
	gameWorld.players[i].no         = i;
	gameWorld.players[i].id         = clients[i].data->client_id;
	gameWorld.players[i].box.x      = 0;
	gameWorld.players[i].box.y      = 0;
	gameWorld.players[i].box.width  = 10;
	gameWorld.players[i].box.height = 10;
	gameWorld.players[i].team       = clients[i].team;

	threads[i] = SDL_CreateThread(&runPlayer, &gameWorld.players[i]);

	if (threads[i] == NULL) {
		printf("\nPlayer SDL_CreateThread failed: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

int assignEvent(int type, char * data, player *p)
{
	/*
	//sleep(5);
	gravity(p, gameWorld.objects, gameWorld.noOfObjects);
	sendToClient(p);

	if (hasInput()) {
		movePlayer(p, gameWorld.objects, gameWorld.noOfObjects, direction);
		sendToClient(p); // Send gameWorld
	}*/
}

int checkConnections()
{
	int i;

	while (1) {
	  for (i = 0; i < NO_PLAYERS; i++) {
		  printf("Beginning of for-loop.\n");
		  if ((clients[i].available == 1) && (accept_session(clients[i].data, PORT, i) == 0)) {
		    printf("Success to establish connection with client %d!\n", i);
		    clients[i].available = 0;
		    clients[i].team      = getAvailableTeam(rand() & 1);
		    printf("Team: %d\n", clients[i].team);
		  }

			/*
			* if (clientDisconnect(i) == 0) {
			*	printf("Player %d disconnected\n", clients[i].id);
			*	SDL_KillThread(threads[i]);
			* 	SDL_KillThread(clients[i].connectionThread);
			*	//SDL_WaitThread(threads[i], &rValue);
			*	clients[i].available = 1;
			*	teams[gameWorld.players[i].team]--;
			*	// sendMessageToClients();
			}
		  printf("End of for-loop.\n");
		  */
		}
	}
}

int checkPlayers()
{
	int i, noPlayers = 0, minTeamPlayers = 0;

	for (i = 0; i < NO_PLAYERS; i++) {
		if (clients[i].available == 0) {
			noPlayers++;
		}
	}

	for (i = 0; i < NO_TEAMS; i++) {
	  //		printf("%d players on team no %d\n", teams[i], i + 1);

		if (teams[i] > 0) {
			minTeamPlayers++;
		}
	}

	return (noPlayers >= 2 && minTeamPlayers == 2);
}

void startGame()
{
	int i;

	for (i = 0; i < NO_PLAYERS; i++) {
		if (clients[i].available == 0) {
			initPlayer(i);
		}
	}
}

int checkGame()
{
  //	printf("Check players output: %d\n", checkPlayers());

	if (state == gEnd) {
		if (checkPlayers()) {
			state = gRunning;
			startGame();
		}
	} else {
		if (!checkPlayers()) {
			state = gEnd;
		}
	}
}

int updatePlayer()
{
	return 5011;
}

void updateObjects()
{
	char string[512];
	int i;
	
	for (i = 0; i < 1; i++) {
		snprintf(string, 512, "2,%d,%d,%d", gameWorld.objects[i].id, gameWorld.objects[i].box.x, gameWorld.objects[i].box.y);
		send_data(clients[i].data, string);
	}
}

int main(int argc, char *argv[])
{
	int i;
	messageBuffer = malloc((sizeof(char*) * NO_PLAYERS));
	char* buffer = NULL;
	int id = 1;
	connection_data * data = malloc(sizeof(connection_data));
	connection_data * genericData = malloc(sizeof(connection_data));

	for (i = 0; i < NO_PLAYERS; i++)
	{
	    messageBuffer[i] = "";
	}
	
	object tmpobject;
	tmpobject.box.x = 100;
	tmpobject.box.y = 0;
	tmpobject.box.width = 10;
	tmpobject.box.height = 10;
	tmpobject.id = 0;
	tmpobject.movable = 0;
	gameWorld.objects[0] = tmpobject;

	printf("Before accept session\n");
	
	for (i = 0; i < 1; i++) {
		accept_session(data, PORT, i+1);
		
		gameWorld.players[i].no         = i;
		gameWorld.players[i].id         = data->client_id;
		gameWorld.players[i].dx         = 1;
		gameWorld.players[i].dy         = 1;
		gameWorld.players[i].mass       = 50;
		gameWorld.players[i].box.x      = 0;
		gameWorld.players[i].box.y      = 0;
		gameWorld.players[i].box.width  = 10;
		gameWorld.players[i].box.height = 10;
		gameWorld.players[i].team       = 0;
		clients[i].available = 0;
		clients[i].data = data;
		clients[i].team = 0;
		threads[i] = SDL_CreateThread(&runPlayer, &gameWorld.players[i]);
	}
	
	genericData = create_connection_data("0.0.0.0", PORT, 0, data->sock_fd, genericData);
	updateObjects();
	
	while(1) {
		//for (i = 0; i < 2; i++) {
			buffer = (char *)recv_data(genericData);
			
			if (buffer != (char*) NULL) {
				id = atoi((char*)strsep(&buffer, ","));
			
				if (id <= NO_PLAYERS) {
					printf("Received buffer data: %s\n", buffer);
					messageBuffer[id] = strdup(buffer);
				}
			}
		//}
	}

	return 0;
}

/*
 Author: 	Joel Denke
 Description: 	Inititate and run clients on the server

int main2(int argc, char *argv[])
{
	// Create server socket to network
	int i, j, rValue, full = 0, state = gEnd;
	nodeList *list = malloc(sizeof(nodeList*));
	char buff[50];
	FILE * fp;

	fp = fopen(LOG, "w");
	_logit(fp, "Start eventhandling");

	insertEnd(list, createNode("test"));
	linkNode * event = list->end;
	lock = SDL_CreateMutex();

	for (i = 0; i < NO_TEAMS; i++) {
		teams[i] = 0;
	}

	for (i = 0; i < NO_PLAYERS; i++) {
		clients[i].available = 1;
		clients[i].data      = malloc(sizeof(connection_data));
	}

	listener = SDL_CreateThread(checkConnections, 0);

	if (listener == NULL) {
		printf("\nListener SDL_CreateThread failed: %s\n", SDL_GetError());
		return 0;
	}

	/*
	// parse level list file into array
	// take random level reference id from array.
	// Then load level text file data, take each row and parse into object struct
	// wait until graphic part decide h

	// Parse the level json (or whatever format we will use) data into object structs.
	// Do not forget to parse the monsters (Panrike, Torgny, Anders m.fl.)
	for (i = 0; i < NO_OBJECTS; i++) {
		gameWorld.objects[i] = NULL;
	}


	event = event->next;
	eCallback * eventCb;

	while (1) {
		checkGame();

		if (state == gEnd) {
			eventCb = (eCallback *)event->data;

			if (eventCb == NULL) {
				event = event->next;
			} else {
			  //				sprintf(buff, "Node data: %d", eventCb->function);
			  //printf(buff);
			  //_logit(fp, buff);
			  event = event->next;
			}
		}
	}
	fclose(fp);
}*/



void _logit(FILE * fp, char *message)
{
	fprintf(fp, "%s\n", message);
}

int sendToClients(char * data)
{
	int i, result;
	printf("Before send data to all clients\n");
	
	for (i = 0; i < 2; i++) {
		if (send_data(clients[i].data, data) != 0) {
			printf("Failed to send data to client %d\n", i);
		} else {
			printf("Test\n");
		}
	}
	
	return 0;
}
	


void runEvent(player * p, char * data)
{
	printf("Runevent: %s\n", data);
	
	if (!strcmp(data, "left")) {
		movePlayer(p, gameWorld.objects, 1, left);
	} else if (!strcmp(data, "right")) {
		movePlayer(p, gameWorld.objects, 1, right);
	} else if (!strcmp(data, "up")) {
		movePlayer(p, gameWorld.objects, 1, up);
	}
}
		

/*
 Author: 	Joel Denke, Marcus Isaksson
 Description: 	Runs the client thread (Listen for user input, moveplayer and synchronize client to server).
 Params: 	parameters	void-pointer to player struct
 Return value:  Always return 0 when thread end
 */
int runPlayer(void* parameters)
{
	player * p = (player*) parameters;
	movement direction = right;
	int rValue;
	char * data = malloc(sizeof(char) * 1500);
	char * send_coord = malloc(sizeof(char) * 1500);

	while (1) {
		SDL_LockMutex(lock);
		data = messageBuffer[p->id];
		messageBuffer[p->id] = "";
		SDL_UnlockMutex(lock);
		
		if (strlen(data) != 0) {
			printf("RunPlayer: %s\n", data);
			runEvent(p, data);
			printf("Before trying to resolve new coordinates\n");
			sprintf(send_coord, "1,%d,%d,%d", p->no, p->box.x, p->box.y);
			printf("Before send coordinate string to clients: (%s)\n", send_coord);
			send_data(clients[p->no].data, send_coord);
			updateObjects();
		}
	}

	return 0;
}
