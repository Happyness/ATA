/**
 * Author
 * Name: Robin Jakobsson / Sarah Larsson
 * Email:    Rjak@kth.se / Saralar@kth.se
 * id:       910724-2696 / 910222-4848
 * Grupp: 2
 */

#ifndef _H_EDITOR
#define _H_EDITOR

#include <SDL.h>
#include <SDL_opengl.h>

#include "structure.h"
#include "draw.h"

#define GUI_HEIGHT 50
/**
 * Author: Robin & Sarah
 * Description: initializes Gui, textures and position
 */
void init_editor(world * gameWorld);
/**
 * Author: Robin
 * Description: Removes the latest created object
 */
void editor_undo(int latest_object,world * gameWorld);
/**
 * Author: Robin & Sarah
 * Description: creates a new object based on property in a free space of the struct
 *
 */
void editor_create_object( int mouse_x, int mouse_y, int property_id, int *free_struct_space ,world * gameWorld);
/**
 * Author: Robin
 * Description: initializing the movement of the object
 *
 */
void editor_start_move_object( int mouse_x, int mouse_y, int *old_mouse_x, int *old_mouse_y);
/**
 * Author: Robin & Sarah
 * Description: checks the top layer and counting down to find the first object that the mouse is pointing on
 *              and moves it to desired place
 */
void editor_update_move_object( int mouse_x, int mouse_y, int *old_mouse_x, int *old_mouse_y ,world * gameWorld);
/**
 * Author: Robin
 * Description: bind diffrent texture to diffrent object property
 *              check editor_show
 */
void bind_texture(int object_id,world * gameWorld);
/**
 * Author: Robin
 * Description: Draws the editor graphics using boxes
 */
void editor_show( int screen_max_x, int screen_max_y ,world * gameWorld);
void editor_save();
void clean_up_editor();

#endif // _H_EDITOR
