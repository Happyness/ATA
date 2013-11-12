/**
 * Contains structs and prototype functions for modifying the game world.
 *
 * Author: Joel Denke, Marcus Isaksson
 * Created:   12 april 2012
 */

#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#define NO_AI  1
#define NO_TEAMS     2
#define NO_PLAYERS   6
#define NO_OBJECTS   100
#define TEST_PLAYERS 6

#define PLAYER_WIDTH   40
#define PLAYER_HEIGHT  40
#define BOX_DX      2
#define BOX_DY      2

#define GRAVITY     0.25
#define FRICTION    0.025

#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

typedef enum {sPlayer, sObject, sCoordinate, sAction, sMessage} sType;
typedef enum {left, right, up, down, jump} movement;
typedef enum {gPause, gStart, gRunning, gEnd, gInit, gExit} gState;
typedef enum {pWon, pPlay} pState;

/**
 * Structure for a "box" in the world.
 *
 */
typedef struct {
	int x, y, width, height, dx, dy;
} box;

/**
 * Structure for a player in the world.
 *
 */
typedef struct {
	int id, team, mass, won, velocity, jump, blockup;
	box box;
	box jumpbox;
	movement direction;
} player;

/**
 * Structure for an ai in the world.
 *
 */
typedef struct {
	int id, mass;
	box box;
	movement direction;
} ai;

/**
 * An object. The world contains a number of blocks which is objects.
 */
typedef struct {
	int id, movable, property;
	box box;
} object;

/**
 * A world contains maximum 6 players and is built of blocks.
 * Each block is an object.
 *
 */
typedef struct {
	player players[NO_PLAYERS];
	object objects[NO_OBJECTS];
	ai	ais[NO_AI];
	int noOfObjects;
} world;

/**
 * contains all the texture inside the game,
 * like characters objects and backgrounds
 */
typedef struct
{
    GLuint load_scr;
    GLuint ready;
    GLuint team1_win;
    GLuint team2_win;
    GLuint couch;
    GLuint floor;
    GLuint wall;
    GLuint stair;
    GLuint fence;
    GLuint table;
    GLuint box;
    GLuint finish;
    GLuint start;
    GLuint player_1;
    GLuint player_2;
    GLuint player_3;
    GLuint player_4;
    GLuint player_5;
    GLuint player_6;
    GLuint background;
    GLuint bg_texture;
    GLuint ip_texture;
} textures;

/**
 * Author: Joel Denke
 * Description: Get map file
 */
char * getMapFile(int);

/**
 * Author: Robin
 * Description: Saves the map to a file named map.dat
 */
void mapSave(world *, int);

/**
 * Author: Robin
 * Description: Load file named map.dat
 * Return value: Last object that has no property id = 0
 */
int mapLoad(world *, int);

#endif
