/**
 * Contains structs and prototype functions for modifying the game world.
 *
 * @author Joel Denke      	mail@happyness.se
 * @author Marcus Isaksson	marcus.is@telia.com
 * @date   12 april 2012
 */

#include <stdio.h>
#include "../graphics/structure.h"
#include "../calc.h"

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

/**
 Author: 	Joel Denke
 Description: 	Function that test a players movement and moves him if legit.
 Params:	player* 	Player you want to move,
		world* 		All objects and players in the world.
		int		No players
		movement* 	Direction player want to go.
 Return value:	1 if no collision and 0 if there is
 */
int movePlayer(player*, world *, int, movement);

/**
 Author: 	Joel Denke, Marcus Isaksson 
 Description: 	Collision detect objects recursively
 Params: 	world* 	All objects and players in the world.
		box	Tmp box of object or player
		int		No players
		int	No tries
		int	Id of object or player
		int	How many steps in x try to move
		int	How many steps in y try to move
 
 Return value:	-1 if no collision and -2 if not legit move
 */
int moveObjects(world *, box, int, int, int, int, int);

/**
 Author: 	Joel Denke           
 Description: 	Let objects fall as well as the player if they are movable
 Params: 	world* 	All objects and players in the world.
		int		No players
 */
void fallObjects(world *, int);

/**
 Author: 	Joel Denke
 Description: 	Function that moves player down by gravity.
 Params:	player* 	Player you want to move,
		world* 		All objects and players in the world.
		int		No players

Return value:	1 if no collision and 0 if there is
 */
void gravity(player*, world *, int);

#endif