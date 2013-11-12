#ifndef _H_WORLD
#define _H_WORLD

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "structure.h"
#include "editor.h"

#define PLAYER_WIDTH 160
#define PLAYER_HEIGHT 216

#define MAX_OBJECTS 100

typedef struct
{
    int jump;
    int cam_x;
    int cam_y;
    float x, y;
    float xVel, yVel;
    float gravity;
    GLuint char_texture;
    GLuint font_texture;
} players;

typedef struct
{
    int property;
    int position_x;
    int position_y;
    int size_x;
    int size_y;
} editor;

typedef struct
{
    GLuint bg_texture;
    int width;
    int height;
} levels;

void player_init( char *file);

void load_level( char *background);

void player_set_xy ( float x, float y);

void player_set_velocity ( float xv, float yv);

void player_set_jump ( int jump);

void camera_move( int screen_max_x, int screen_max_y);

void player_move( int screen_maxx, int screen_maxy);

void player_jump( int screen_maxy);
void drawBox(box *, SDL_Color *);
void drawPlayers(player *, int);
void drawObjects(object *, int);

//void world_show( int screen_max_x, int screen_max_y );

void clean_up_world();

#endif

