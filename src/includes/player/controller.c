#include "controller.h"

int movePlayer(player* p, world * gWorld, int no_players, movement direction)
{
	 int i, x = 0, y = 0, move;
	 box tmpbox = p->box;
	 int length = calculateLengthToMove(tmpbox, direction);

	 //printf("player %d was on coordinate [%d, %d]\n", p->id, tmpbox.x, tmpbox.y);

	 switch (direction) {
		 case left :
			 x -= length;
			 tmpbox.x += x;
			 break;
		 case right :
			 x += length;
			 tmpbox.x += x;
			 break;
		 case up :
			y -= length*20;
			tmpbox.y += y;
			 break;
	 }
	 
	 //printf("Try to move player %d [%d, %d]\n", p->id, x, y);

	 move = moveObjects(gWorld, tmpbox, no_players, p->id, -1, x, y);

	 if (move == -1) {
		 if (tmpbox.y > 600 || tmpbox.y < 0) {
			 printf("You tried walk outside screen\n");
			 p->velocity = 0;
			 p->blockup = 1;
		 } else if (tmpbox.x < 800 && tmpbox.x > 0) {
			 p->box = tmpbox;
		}
		 //printf("player %d is now on coordinate [%d, %d]\n", p->id, tmpbox.x, tmpbox.y);
		 return 1;
	 } else {
		 return 0;
	 }
}

int checkPlayerCollision(world * gWorld, int no_players, int pId, box tile)
{
	int i;
	
	for (i = 0; i < no_players; i++) {
		if (gWorld->players[i].id != pId && isCollision(gWorld->players[i].box, tile)) {
			return 0;
		}
	}
	
	return 1;
}

int moveObjects(world * gWorld, box tmpbox, int no_players, int pId, int id, int x, int y)
{
	int i;

	for (i = 0; i < NO_OBJECTS; i++)
	{
		if (i != id && i != 0 && i!= 1) {
			if (isCollision(tmpbox, gWorld->objects[i].box)) {
				if (gWorld->objects[i].movable)
				{
					box tmpbox2 = gWorld->objects[i].box;
					
					tmpbox2.x += x;
					tmpbox2.y += y;
					
					if (checkPlayerCollision(gWorld, no_players, pId, tmpbox2)) {
						if (moveObjects(gWorld, tmpbox2, no_players, pId, i, x, y) == -1)
						{
							gWorld->objects[i].box = tmpbox2;
							return -1;
						} else {
							return -2;
						}
					} else {
						return -2;
					}
				}

				return -2;
			}
		}
	}

	if (id != -1) {
		gWorld->objects[id].box.x += x;
		gWorld->objects[id].box.y += y;
		
		if (checkPlayerCollision(gWorld, no_players, pId, gWorld->objects[id].box)) {
			return -1;
		} else {
			return -2;
		}
	}

	return -1;
}

void fallObjects(world * gWorld, int no_players)
{
	int i, move, y, x=0;
	box tmpbox;
	movement direction = down;

	for (i = 0; i < NO_OBJECTS; i++) {
		if (gWorld->objects[i].movable) {
			tmpbox    = gWorld->objects[i].box;
			y         = calculateLengthToMove(tmpbox, direction);

			tmpbox.y += y;

			move = moveObjects(gWorld, tmpbox, no_players, -1, -1, x, y);

			if (move == -1) {
				gWorld->objects[i].box = tmpbox;
				//printf("Object %d is now on coordinate [%d, %d]\n", gWorld->objects[i].id, tmpbox.x, tmpbox.y);
			}
		}
	}
}

void gravity(player* p, world * gWorld, int no_players)
{
	 int i, move, y = 0;
	 box tmpbox         = p->box;
	 movement direction = down;

	 y = calculateLengthToMove(p->box, direction);
	 tmpbox.y += y + p->velocity;

	 move = moveObjects(gWorld, tmpbox, no_players, -1, -1, 0, y);

	 if (move == -1) {
		 p->box = tmpbox;
		 //printf("player %d is now on coordinate [%d, %d]\n", testPlayer->id, tmpbox.x, tmpbox.y);
	 } else {
		p->jump = 0;
		p->blockup = 0;
		p->velocity = 5;
	 }
}
