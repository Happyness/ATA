/**
* Contains structs and funktions for modifying the game world.
*
* @author Joel Denke      - mail@happyness.se
* @author Marcus Isaksson - marcus.is@telia.com
* @date   12 april 2012
*/

#define NO_PLAYERS 6
#define NO_OBJECTS 100

enum movement {left, right};

/**
 * Structure for a player in the world.
 *
 */
struct player {
	int id, x, y, width, height, team;
};

/**
 * An object. The world contains a number of blocks which is objects.
 */
struct object {
	int id, x, y, width, height;
};

/**
 * A world contains maximum 6 players and is built of blocks.
 * Each block is an object.
 *
 */
struct world {
	struct player players[NO_PLAYERS];
	struct object objects[NO_OBJECTS];
};

/**
 * Function that test a players movement and
 * moves him if legit.
 *
 *@param testPlayer is a pointer to the player you want to move,
 *@param objects is a pointer to a array containing all objects in the world.
 *@param noOfObjects is the number of objects in the objects array.
 *@param direction is a enum telling which direction you want to go.
 */
void MovePlayer(struct player* testPlayer, int x, int y)
{
    testPlayer->x = x;
    testPlayer->y = y;
}
