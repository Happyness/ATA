/**
 * Author
 * Name: Robin Jakobsson / Sarah Larsson
 * Email:    Rjak@kth.se / Saralar@kth.se
 * id:       910724-2696 / 910222-4848
 * Grupp: 2
 */
#ifndef _H_MENU
#define _H_MENU

#include <SDL.h>
#include <SDL_opengl.h>
#include <string.h>

#include "draw.h"

#define BUTTON_HEIGHT 50
#define BUTTON_WIDTH 200

typedef struct
{
    GLuint menu_bg_texture;
    GLuint button_play;
    GLuint button_options;
    GLuint button_editor;
    GLuint button_exit;
    GLuint button_back;
} menuTexture;

typedef struct
{
    menuTexture butText;
    int button_statement;
    int x_play;
    int y_play;
    int x_options;
    int y_options;
    int x_editor;
    int y_editor;
    int x_exit;
    int y_exit;
} menu;

/**
 * Author: Robin & Sarah
 * Description: Initializing the buttons, backgrounds, offset..etc..
 */
int load_menu( char *background, char *play, char *options, char *editor, char *exit, char *back, int screen_maxX, int screen_maxY);
/**
 * Author: Robin & Sarah
 * Description: Checks positioning for the mouse compared to buttons
 */
int check_menu( int mouse_x, int mouse_y );
/**
 * Author: Robin & Sarah
 * Description: Switches texture on button while hovering the mouse over it.
 *
 */
void mouse_over_menu( int mouse_x, int mouse_y );

/**
 * Author: Robin
 * Description: Switches texture on button while clicking the mouse on it.
 *
 */
int mouse_down_menu( int mouse_x, int mouse_y );

/**
 * Author: Sarah
 * Description: checks if any button was pressed and continues from the users option.
 *
 */
int press_menu( int mouse_x, int mouse_y );
int check_options(int mouse_x, int mouse_y);
int press_options(int mouse_x, int mouse_y);

/**
 * Author: Robin
 * Description: handle input and copy it to the string.
 *
 */
void handle_input(SDL_Event event, char str[]);

void drawBack();
/**
 * Author: Robin & Sarah
 * Description: Draw the menu using boxes starting with background and working to the top layers.
 *
 */
void drawMenu( int screen_max_x, int screen_max_y );
/**
 * Author: Robin
 * Description: Frees the texture so we dont have memory leaking..
 *
 */
void clean_up_menu();

#endif // MENU_H_INCLUDED
