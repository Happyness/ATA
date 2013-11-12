#include "ai.h"

#define MAX_X 20

int startx, starty;

int initAI(world * gWorld)
{
	printf("Try to init AI to coordinate [%d, %d]\n", gWorld->objects[0].box.x - gWorld->objects[0].box.width - 1, gWorld->ais[0].box.y);
	gWorld->ais[0].box.x = gWorld->objects[0].box.x - gWorld->objects[0].box.width - 1;
	gWorld->ais[0].box.y = gWorld->objects[0].box.y;
	startx = gWorld->ais[0].box.x;
	starty = gWorld->ais[0].box.y;
}

void moveAI(world *gWorld)
{
	int x = 0, y = 0, move;
	box tmpbox = gWorld->ais[0].box;
	int length = calculateLengthToMove(tmpbox, gWorld->ais[0].direction);
	
	if ((abs(startx - gWorld->ais[0].box.x)) < MAX_X) {
		switch (gWorld->ais[0].direction) {
			case left :
				x -= length;
				tmpbox.x += x;
				break;
			case right :
				x += length;
				tmpbox.x += x;
				break;
		}
		
		printf("Try to move AI to coordinate [%d, %d]\n", tmpbox.x, tmpbox.y);
		move = moveObjects(gWorld, tmpbox, -1, -1, x, y);
		
		if (move == -1) {
			gWorld->ais[0].box = tmpbox;
		} else {
			swithDirection(gWorld);
		}
	} else {
		swithDirection(gWorld);
	}
}

void swithDirection(world * gWorld)
{
	switch (gWorld->ais[0].direction) {
		case left :
			gWorld->ais[0].direction = right;
			break;
		case right :
			gWorld->ais[0].direction = left;
			break;
	}
}