#include "world/world.h"
#include "stdlib.h"
#include "SDL.h"

//Function prototypes
void DisplayState(SDL_KeyboardEvent *key);
void DisplayModifiers(SDL_KeyboardEvent *key);
void DisplayKey(SDL_KeyboardEvent *key);

int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	SDL_Event event;
	int running = 1;
	
	//We must first initialize the SDL video component, and check for success
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	//When this program exits, SDL_Quit must be called
	atexit(SDL_Quit);
	
	//Set the video mode to anything, just need a window
	screen = SDL_SetVideoMode(320, 240, 0, SDL_ANYFORMAT);
	
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	
	//Keep looping until the user closes the SDL window
	while (running) {
		//Get the next event from the stack
		while(SDL_PollEvent(&event)) {
			//What kind of event has occurred?
			switch (event.type) {
				case SDL_KEYDOWN :
					/* Check the SDLKey values and move change the coords */
					switch (event.key.keysym.sym) {
						case SDLK_LEFT:
							//alien_x -= 1;
							break;
						case SDLK_RIGHT:
							//alien_x += 1;
							break;
						case SDLK_UP:
							//alien_y -= 1;
							break;
						case SDLK_DOWN:
							//alien_y += 1;
							break;
						default:
							break;
					}
					
						case SDL_KEYUP:		//A key has been released
					DisplayState(&event.key);	//Print out the key state
					DisplayModifiers(&event.key);	//Print out the key modifiers
					DisplayKey(&event.key);		//Print out the key itself
					break;
						case SDL_QUIT:		//The user has closed the SDL window
					running = 0;
					break;
			}
		}
	}
	
	//Return success!
	return 0;
}

void DisplayState(SDL_KeyboardEvent *key)
{
	//What type of keypress was this?
	if (key->type == SDL_KEYUP)
		printf("RELEASED: ");
	else
		//char * string = SDL_GetKeyName(key->keysym.sym);
	printf("PRESSED: ");
	
}

void DisplayModifiers(SDL_KeyboardEvent *key)
{
	//What modifiers were held down when the keyboard event took place?
	SDLMod modifier = key->keysym.mod;
	if( modifier & KMOD_NUM ) printf( "NUMLOCK " );		//Numlock modifier
	if( modifier & KMOD_CAPS ) printf( "CAPSLOCK " );	//Capslock modifier
	if( modifier & KMOD_MODE ) printf( "MODE " );		//Special "Mode" modifier
	if( modifier & KMOD_LCTRL ) printf( "LCTRL " );		//Left control key modifier
	if( modifier & KMOD_RCTRL ) printf( "RCTRL " );		//Right control key modifier
	if( modifier & KMOD_LSHIFT ) printf( "LSHIFT " );	//Left shift key modifier
	if( modifier & KMOD_RSHIFT ) printf( "RSHIFT " );	//Right shift key modifier
	if( modifier & KMOD_LALT ) printf( "LALT " );		//Left alt key modifier
	if( modifier & KMOD_RALT ) printf( "RALT " );		//Right alt key modifier
	if( modifier & KMOD_LMETA ) printf( "LMETA " );		//Left meta (Apple 'Command') key modifier
	if( modifier & KMOD_RMETA ) printf( "RMETA " );		//Right meta (Apple 'Command') key modifier
	
	//The following are included for completeness, but would give duplicate output if used with the code above
	//if( modifier & KMOD_CTRL ) printf( "CTRL " );		//Left or right control key modifier
	//if( modifier & KMOD_SHIFT ) printf( "SHIFT " );	//Left or right shift key modifier
	//if( modifier & KMOD_ALT ) printf( "ALT " );		//Left or right alt key modifier
	//if( modifier & KMOD_META ) printf( "META " );		//Left or right meta (Apple 'Command') key modifier
}

void DisplayKey(SDL_KeyboardEvent *key)
{
	//Print out text corresponding to the key in question
	printf( "%s\n", SDL_GetKeyName(key->keysym.sym));
}