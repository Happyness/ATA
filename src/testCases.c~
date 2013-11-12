// System headers
#include <stdio.h>
#include <stdlib.h>

// User headers
#include "includes/graphics/structure.h"
#include "includes/calc.h"
#include "includes/cbuffer.h"

world * gameWorld;

void printWorld()
{
	int i;
	player p;
	object b;
	
	printf("------------ Print world data ----------------\n");
	
	/*
	for (i = 0; i < TEST_PLAYERS; i++) {
		p = gameWorld.players[i];
		printf("Player %d, contains [%d %d %d %d]\n", p.id, p.box.x, p.box.y, p.box.width, p.box.height);	
	}*/
	
	for (i = 0; i < NO_OBJECTS; i++) {
		b = gameWorld->objects[i];
		printf("Object %d, contains [%d %d %d %d]\n", b.id, b.box.x, b.box.y, b.box.width, b.box.height);	
	}
	
	printf("----------------- End of world data ------------------------\n");
}

int testMap()
{
	world * gameWorld = malloc(sizeof(world));
	
	object tmpobject;
	tmpobject.box.x = 100;
	tmpobject.box.y = 500;
	tmpobject.box.width = 100;
	tmpobject.box.height = 80;
	tmpobject.id = 0;
	tmpobject.movable = 0;
	gameWorld->objects[0] = tmpobject;
	
	object tmpobject2;
	tmpobject2.box.x = 0;
	tmpobject2.box.y = 580;
	tmpobject2.box.width = 800;
	tmpobject2.box.height = 10;
	tmpobject2.id = 1;
	tmpobject2.movable = 0;
	gameWorld->objects[1] = tmpobject2;
	
	mapSave(gameWorld, MAP_FILE);
}

int testCollision()
{
	box a, b;
	
	a.x = 0;
	a.y = 0;
	a.width = 10;
	a.height = 10;
	
	b.x = -10;
	b.y = 10;
	b.width = 10;
	b.height = 10;
	
	if (isCollision(a, b)) {
		printf("Collision detected!\n");
		return 1;
	} else {
		printf("No collision!");
		return 2;
	}
}


int testcBuffer()
{
	cBuffer * cb = malloc(sizeof(cBuffer));
	char * elem = malloc(sizeof(slot));
	int i;
	int testBufferSize = 10;
	char data[1500];
	initSlots(cb, testBufferSize);
	
	for (i = 0; i < testBufferSize * 3; i++) {
		sprintf(data, "testBuffer: %d", i);
		writeSlot(cb, strdup(data));
	}

	while (!slotsEmpty(cb)) {
		elem = readSlot(cb);
		printf("%s\n", elem);
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	testMap();
	testcBuffer();
	testCollision();
}