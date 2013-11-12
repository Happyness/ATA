/* Author
 * Name: Robin Jakobsson / Sarah Larsson
 * Email:    Rjak@kth.se /
 * id:       910724-2696 /
 * Grupp:
 */
#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

#define FRAMES_PER_SECOND 60

/*
 * Author: Robin
 * Description: initializing opengl and set the screen view to pixels used so
 *              its much easyer to program. Also Enable Alpha blending so we
 *              are able to use transparenty on textures.
 *
 */
int init_GL();

/*
 * Author: Robin
 * Description: initializing SDL and some textures, also set the program icon and caption
 *
 */
int init();
/*
 * Author: Robin
 * Description: Clean up every texture by sending the adress to each function
 *              and from there we use gldeletetexture
 */
void clean_up();

/*
 * Author: Robin & Sarah
 * Description: This function is activ while playing, it handles input from user
 *              it also initializes background texture, player texture, player starting point
 *              set text color and font. Draw the screen
 */
void playing();
/*
 * Author: Robin & Sarah
 * Description: handles input to create and edit objects, draw the map.
 *              Save the map using a binary text file
 */
void in_editor();
/*
 * Author: Robin & Sarah
 * Description: initializing textures button positions etc..
 *              handle mouse events so we are able to use our menu
 */
void in_menu();

#endif