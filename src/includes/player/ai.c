 // Inkludera bibliotek för grafik här
 #include <stdio.h>
 #include "../world/structure.h"
 #include "controller.h"
 #include "../libcalc.h"
  
 
 void movePlayer(struct player* testPlayer, struct object * objects, int noOfObjects, enum movement direction)
 {
	 int i, collision = 0, objectCollided = -1;
	 struct box tmpbox = testPlayer->box;
	 
	 switch (direction) {
		 case left :
			 tmpbox.x -= calculateLengthToMove(testPlayer, direction);
			 break;
		 case right :
			 tmpbox.x += calculateLengthToMove(testPlayer, direction);
			 break;
		 case up :
			 tmpbox.y -= calculateLengthToMove(testPlayer, direction);
			 break;
	 }
	 
	 for (i = 0; i < noOfObjects; i++) {
		 if (isCollision(tmpbox, objects[i].box)) {
			 collision = 1;
			 objectCollided = i;
			 break;
		 }
	 }
	 
	 if (!collision) {
		 testPlayer->box = tmpbox;
	 } else {
		 // Ska bossarna kunna flytta på objekt? :S
	 }
 }