#ifndef _C_LOAD_FONT
#define _C_LOAD_FONT

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#include <math.h>

#include "load_font.h"



void init_font(/* char *font */)
{
    font = TTF_OpenFont("font/comicbd.ttf"/*font*/, 20);
    printf("font loading\n");
    if(!font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
}

void set_text_color( int RED, int GREEN, int BLUE )
{
    colors.r = RED;
    colors.g = GREEN;
    colors.b = BLUE;
}


int nextpoweroftwo(int x)
{
	double logbase2 = log(x) / log(2);
	return round(pow(2,ceil(logbase2)));
}

void load_text( char *text )
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    printf("start texture");
    SDL_Rect area;
    SDL_Color clrFg = {0,0,255,0};
    printf("imsomad");
    SDL_Surface *sText = SDL_DisplayFormatAlpha(TTF_RenderUTF8_Blended( font, text, clrFg ));
    printf("middlefirst");
    area.x = 0;area.y = 0;area.w = sText->w;area.h = sText->h;
    SDL_Surface* temp = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA,sText->w,sText->h,32,0x000000ff,0x0000ff00,0x00ff0000,0x000000ff);
    SDL_BlitSurface(sText, &area, temp, NULL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sText->w, sText->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
    printf("Middle");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glBegin(GL_QUADS);
    {
        glTexCoord2d(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2d(1, 0); glVertex3f(0 + sText->w, 0, 0);
        glTexCoord2d(1, 1); glVertex3f(0 + sText->w, 0 + sText->h, 0);
        glTexCoord2d(0, 1); glVertex3f(0, 0 + sText->h, 0);
    }
    glEnd();
    printf("finished rendering text");
    SDL_FreeSurface( sText );
    SDL_FreeSurface( temp );
    glDisable(GL_BLEND);
}



#endif
