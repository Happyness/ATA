#ifndef _C_LEVEL
#define _C_LEVEL

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "level.h"

void load_level(struct level_t3 * level, char *background)
{
    level->bg_texture = load_imageRGBA(background);
}

void show_level(struct level_t3 * level,int screen_max_x,int screen_max_y)
{

}

#endif
