/*
 Author: 	Joel Denke and Marcus Isaksson
 Description: 	Runs the client, draw graphics and handle inputs.
 Created:	13 april 2012
 */

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
//#include "includes/graphic/graphic.c"
#include "includes/network/udp_protocol.h"
#include "includes/graphics/structure.h"
#include "includes/linkedList.h"
#include "includes/graphics/world.h"
#include "includes/graphics/timer.h"
#include "includes/graphics.h"

world gameWorld;
SDL_Event event;
int keysHeld[323] = {0}; // everything will be initialized to false
int gameRunning = 0;

#define WIDTH 640
#define HEIGHT 480
#define BPP 4
#define DEPTH 32
#define FRAMES_PER_SECOND 60

char* messageBuffer;
connection_data *connection;
SDL_mutex  *lock;
SDL_mutex  *networkMutex;
SDL_Color * pColor;
SDL_Color * oColor;
nodeList * list;

int clientConnect(connection_data * connection)
{
	char* client_ip = "127.0.0.1";
	char * server_ip = "127.0.0.1";
	uint32_t server_port = 1025;

	/*
	printf("Type client data [usage; client ip, port]:\n");

	check_input = scanf("%s %d", &client_ip, &client_port);

	if (check_input < 2) {
		printf("Error during client data input\n");
	}

	printf("Type server data [usage; server ip]:\n");

	check_input = scanf("%s %d", &server_ip);

	if (check_input < 2) {
		printf("Error during client data input\n");
	}
	*/

	printf("--------- Start trying to connect client: %p -----------\n", connection);

	return connect_session(connection, server_ip, server_port, client_ip);
}

void movePlayer(char * movement)
{
	char string[512];
	
	printf("before send right\n");
	snprintf(string, 512, "%d,%s", connection->client_id, movement);
	printf("Sent data: %s\n", string);
	
	if (send_data(connection, string) != 0) {
		printf("Didnt send right movement to server correctly\n");
	}
}

void listenInput(connection_data * connection)
{
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN :
				keysHeld[event.key.keysym.sym] = 1;
				break;
			case SDL_KEYUP :
				keysHeld[event.key.keysym.sym] = 0;
				break;
			case SDL_QUIT :
				//end_session(connection);
				clean_up();
				exit(0);
				break;
		}
	}
	
	if (keysHeld[SDLK_ESCAPE])
	{
		gameRunning = 0;
	}
	
	if ( keysHeld[SDLK_LEFT] )
	{
		movePlayer("left");
	}
	
	if (keysHeld[SDLK_RIGHT])
	{
		movePlayer("right");
	}
	
	if ( keysHeld[SDLK_UP] )
	{
		movePlayer("up");
	}
}

int listenEventBuffer()
{
	int id;
	char * buffer;
	char * eData;
	
	while(gameRunning) {
		buffer = (char*)recv_data(connection);
		
		if (buffer != (char*)NULL) {
			//SDL_LockMutex(lock);
			printf("Before insert message (%s) into buffer que\n", buffer);
			//runEvent(buffer);
			//messageBuffer = strdup(buffer);
			//SDL_UnlockMutex(lock);
			insertEnd(list, createNode(strdup(buffer)));
		}
	}
	
	return 0;
}

void drawGraphics()
{
	int i;
	
	for (i = 0; i < 1; i++) {
		drawBox(&gameWorld.objects[i].box, oColor);
	}
	
	for (i = 0; i < 1; i++) {
		drawBox(&gameWorld.players[i].box, pColor);
	}
}
		

void runEvent(char * eventData)
{
	int type, id, x , y;
	
	type = atoi((char*)strsep(&eventData, ","));
	id = atoi((char*)strsep(&eventData, ","));
	x = atoi((char*)strsep(&eventData, ","));
	y = atoi((char*)strsep(&eventData, ","));
	
	printf("Runevent with id: %d and data (%s)\n", id, eventData);
	
	switch (type) {
		case 1:
			printf("Change player coordinate to [%d, %d]", x ,y);
			gameWorld.players[id].box.x = x;
			gameWorld.players[id].box.y = y;
			break;
		case 2:
			printf("Change object coordinate to [%d, %d]", x ,y);
			gameWorld.objects[id].box.x = x;
			gameWorld.objects[id].box.y = y;
			break;
	}
}

/*
int runEventBuffer()
{
	char * data;
	
	while (gameRunning) {
		SDL_LockMutex(lock);
		data = messageBuffer;
		messageBuffer = "";
		SDL_UnlockMutex(lock);
		
		if (strlen(data) != 0) {
			runEvent(data);
		}
	}
	
	return 0;
}*/

void initPlayer(int i, connection_data * connection)
{
	player p;
	gameWorld.players[i]            = p;
	gameWorld.players[i].no         = i;
	gameWorld.players[i].id         = connection->client_id;
	gameWorld.players[i].box.x      = 0;
	gameWorld.players[i].box.y      = 0;
	gameWorld.players[i].box.width  = 100;
	gameWorld.players[i].box.height = 100;
	gameWorld.players[i].team       = 0;
}

int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	SDL_Thread * eventBuffer;
	SDL_Thread * runBuffer;
	char* buffer = NULL;
	char* eData = malloc(sizeof(char)*1500);
	int i;
	
	pColor = malloc(sizeof(SDL_Color));
	pColor->r = 0;
	pColor->g = 255;
	pColor->b = 255;
	oColor = malloc(sizeof(SDL_Color));
	oColor->r = 0;
	oColor->g = 0;
	oColor->b = 255;
	
	init();
	//printf("Result of graphics: %d\n", loadGraphics());

	char string[512];

	connection = malloc(sizeof(connection_data));

	//printf("Argv[0]: %s == %d\n", argv[1], atoi(argv[1]));

	//if (clientConnect(connection, atoi(argv[1])) == 0) {
	//	printf("Success to connect to server!\n");
		//printf("Buffer: %s", getData(connection));
	//	printf("Ending session.\n");
	//	end_session(connection);
	//}
	
	object tmpobject;
	tmpobject.box.x = 100;
	tmpobject.box.y = 0;
	tmpobject.box.width = 100;
	tmpobject.box.height = 100;
	tmpobject.id = 0;
	tmpobject.movable = 0;
	gameWorld.objects[0] = tmpobject;
	
	struct timer_t2 fps;
	list = malloc(sizeof(nodeList));
	linkNode * event = malloc(sizeof(linkNode));
	event->next = NULL;
	
	//messageBuffer = malloc(sizeof(char) * 1500);
	//char * data = malloc(sizeof(char) * 1500);
	//messageBuffer = "";
	//data = "";
	
	SDL_Color * color = malloc(sizeof(SDL_Color));
	color->r = 0;
	color->g = 255;
	color->b = 255;

	if (clientConnect(connection) == 0) {
		initPlayer(0, connection);
		drawBox(&gameWorld.players[0].box, color);
		gameRunning = 1;
		eventBuffer = SDL_CreateThread(listenEventBuffer, &connection);
		//runBuffer   = SDL_CreateThread(runEventBuffer, NULL);

		while (gameRunning) {
			timer_start(&fps);
			listenInput(connection);
			
			//Capture the frame rate
			if (timer_get_ticks(&fps) < 1000 / FRAMES_PER_SECOND )
			{
				//delay the as much time as we need to get desired frames per second
				SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - timer_get_ticks(&fps) );
			}
			
			/*SDL_LockMutex(lock);
			data = messageBuffer;
			messageBuffer = "";
			SDL_UnlockMutex(lock);
			
			if (strlen(data) != 0) {
				runEvent(data);
				drawGraphics();
			}*/
			
			if (event->next != list->end) {
				eData = (char*)event->data;
				//list->current = event;
				
				if (eData != (char*)NULL) {
					printf("Data from current buffer element: %s\n", eData);
					runEvent(eData);
					drawGraphics();
					//removeNode(list, event);
					event = event->next;
				}
			}
		}
	}

	return 0;
}

int main2(int argc, char *argv[])
{
	/*
	cs = connectServer();
	getPlayers();
	drawWorld();

	while (isConnected()) {
		sendInputToServer();
		getPlayers();
		updateWorldToServer();
		drawGraphics();
	}*/
}
