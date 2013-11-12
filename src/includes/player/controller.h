/**
 * Contains structs and prototype functions for modifying the game world.
 *
 * @author Joel Denke      	mail@happyness.se
 * @author Marcus Isaksson	marcus.is@telia.com
 * @date   12 april 2012
 */

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

/**
 * Function that test a players movement and
 * moves him if legit.
 *
 *@param testPlayer 	Player you want to move,
 *@param objects 	All objects in the world.
 *@param noOfObjects 	Number of objects in the objects array.
 *@param direction 	Direction you want to go.
 */
void movePlayer(player*, object *, int, movement);
/**
 * A function that test if a player should be falling
 * and moves him if so.
 *
 *@param testPlayer 	Player you want to move,
 *@param objects 	All objects in the world.
 *@param noOfObjects 	Number of objects in the objects array.
 */
void gravity(player*, object *, int);

#endif