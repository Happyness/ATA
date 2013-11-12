#ifndef _C_LOAD_IMAGE
#define _C_LOAD_IMAGE

#include <SDL.h>
#include <SDL_opengl.h>

#include "load_image.h"

/*
 *   Author: Robin
 *   Load up the image from any RGBA using image through SDL and convert it to openGL
 *
 *   *****IMPORTANT*****
 *   You can not use any image while using this. The image has to use RGBA setup (ALPHA technique)
 *   else the pixels will be pushed and the image will be a completly mess.
 *
 */

int load_imageRGBA(char *file)
{
	char string[1000];
	sprintf(string, "%s%s", "/home/joel/Dropbox/KTH/HI1026 - Projektarbete och Internetteknik/Projektarbete/complete/src/textures/", file);
	SDL_Surface *tex = IMG_Load(string); //textures/file.png
    
    GLuint texture = 0;

    if(tex)
    {
        //SDL_SetAlpha(tex,SDL_SRCALPHA,0);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h,
        0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SDL_FreeSurface(tex);
    }
    else
    {
        printf("Texture couldn't load (%s)\n",file);
        clean_up();
        exit(-1);
    }
    //printf("Texture loaded correctly %s\n",file);
    return texture;
}



#endif
