#ifndef _H_LOAD_FONT
#define _H_LOAD_FONT

SDL_Color colors;
TTF_Font *font;

void init_font( /*char *font*/);

void set_text_color( int RED, int GREEN, int BLUE );

void load_text( char *text );

#endif // _H_LOAD_FONT
