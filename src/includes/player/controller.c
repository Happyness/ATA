// Inkludera bibliotek för grafik här
#include <stdio.h>
#include "../graphics/structure.h"
#include "controller.h"
#include "../libcalc.h"
#include "playerInput.c"
 
void movePlayer(player* testPlayer, object * objects, int noOfObjects, movement direction)
{
	 int i, collision = 0, objectCollided = -1;
	 box tmpbox = testPlayer->box;
	 
	 printf("player %d was on coordinate [%d, %d]\n", testPlayer->no, tmpbox.x, tmpbox.y);
	 printf("Check enum value %d on move\n", direction);
	 
	 switch (direction) {
		 case left :
			 printf("Move player left %d steps \n", calculateLengthToMove(testPlayer, direction));
			 tmpbox.x -= calculateLengthToMove(testPlayer, direction);
			 break;
		 case right :
			 printf("Move player right %d steps \n", calculateLengthToMove(testPlayer, direction));
			 tmpbox.x += calculateLengthToMove(testPlayer, direction);
			 break;
		 case up :
			 tmpbox.y -= calculateLengthToMove(testPlayer, direction);
			 break;
		 default :
			 break;
	 }
	 
	 for (i = 0; i < noOfObjects; i++) {
		 printf("testCollision\n");
		 
		 if (isCollision(tmpbox, objects[i].box)) {
			 collision = 1;
			 objectCollided = i;
			 break;
		 }
	 }
	 
	 if (!collision) {
		 testPlayer->box = tmpbox;
		 printf("player %d is now on coordinate [%d, %d]\n", testPlayer->no, tmpbox.x, tmpbox.y);
	 } else {
		printf("Player collidated with object %d on coordinate [%d, %d]\n", objects[objectCollided].id, objects[objectCollided].box.x, objects[objectCollided].box.y);
		 
		if (objects[objectCollided].movable) {
			objects[objectCollided].box.x += testPlayer->dx;
			objects[objectCollided].box.y += testPlayer->dy;
		}
	 }
}
 
void gravity(player* testPlayer, object * objects, int noOfObjects)
{
	 int i, collision        = 0;
	 box tmpbox       = testPlayer->box;
	 movement direction = down;
	 
	 tmpbox.y += calculateLengthToMove(testPlayer, direction);
	 
	 for (i = 0; i < noOfObjects; i++) {
		 if (isCollision(tmpbox, objects[i].box)) {
			 collision = 1;
			 break;
		 }
	 }
	 
	 if (!collision) {
		 testPlayer->box = tmpbox;
	 }
}