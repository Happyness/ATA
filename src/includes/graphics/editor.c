#ifndef _C_EDITOR
#define _C_EDITOR

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "editor.h"
#include "world.h"
#include "structure.h"

editor objects[MAX_OBJECTS];

/*
 * Author: Robin & Sarah
 * Description: initializes Gui, textures and position
 */
void init_editor()
{
	char * interface = "editor_gui.png";
	char * couch = "soffa.png";
	
	printf("before Load images\n");
	
	texture.gui = load_imageRGBA(interface);
	texture.couch = load_imageRGBA(couch);
	
	printf("After load images\n");
	int i;
	
	for (i=0;i<MAX_OBJECTS;i++) {
		objects[i].property = 0;
		objects[i].position_x = 0;
		objects[i].position_y = 0;
		objects[i].size_x = 0;
		objects[i].size_y = 0;
	}
}
/*
 * Author: Robin
 * Description: Removes the latest created object
 */
void editor_undo(int latest_object)
{
    objects[latest_object].property = 0;
    objects[latest_object].position_x = 0;
    objects[latest_object].position_y = 0;
    objects[latest_object].size_x = 0;
    objects[latest_object].size_y = 0;
}
/*
 * Author: Robin & Sarah
 * Description: creates a new object based on property in a free space of the struct
 *
 */
void editor_create_object( int mouse_x, int mouse_y, int property_id, int *free_struct_space )
{
    int i;
    for(i=0;i<MAX_OBJECTS;i++)
    {
        if(objects[i].property == 0)
        {
            *free_struct_space = i;
            break;
        }
    }
    switch(property_id)
    {
        case 1:
            objects[*free_struct_space].property = property_id;
            objects[*free_struct_space].size_x = 200;
            objects[*free_struct_space].size_y = 70;
            objects[*free_struct_space].position_x = mouse_x - (objects[*free_struct_space].size_x / 2);
            objects[*free_struct_space].position_y = mouse_y - (objects[*free_struct_space].size_y / 2);
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        default:
            break;
    }
}

/*
 * Author: Robin
 * Description: initializing the movement of the object
 *
 */
void editor_start_move_object( int mouse_x, int mouse_y, int *old_mouse_x, int *old_mouse_y )
{
    *old_mouse_x = mouse_x;
    *old_mouse_y = mouse_y;
}

/*
 * Author: Robin & Sarah
 * Description: checks the top layer and counting down to find the first object that the mouse is pointing on
 *              and moves it to desired place
 */
void editor_update_move_object( int mouse_x, int mouse_y, int *old_mouse_x, int *old_mouse_y )
{
    int i;
    for(i=MAX_OBJECTS-1;i>=0;i--)
    {
        if( (mouse_x > objects[i].position_x) && (mouse_x < objects[i].position_x + objects[i].size_x) )
        {
            if( (mouse_y > objects[i].position_y) && (mouse_y < objects[i].position_y + objects[i].size_y) )
            {
                objects[i].position_x += mouse_x - *old_mouse_x;
                objects[i].position_y += mouse_y - *old_mouse_y;
                break;
            }
        }
    }
    *old_mouse_x = mouse_x;
    *old_mouse_y = mouse_y;
}

/*
 * Author: Robin
 * Description: bind diffrent texture to diffrent object property
 *              check editor_show
 */
void bind_texture(int object_id)
{
    switch(objects[object_id].property)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        default:
            glBindTexture(GL_TEXTURE_2D, texture.couch);
            break;
    }
    //glBindTexture(GL_TEXTURE_2D, object[i].object_texture);
}

/*
 * Author: Robin & Sarah
 * Description: Draw the screen using boxes and some triangles starting with background and moving forward.
 *
 */
void editor_show( int screen_max_x, int screen_max_y )
{
    glTranslatef(0,0,0);
    int i,j,used_objects = 0;

    for(j=0; j<MAX_OBJECTS; j++)
    {
        if(objects[j].property == 0)
        {
            break;
        }
        else
        {
            used_objects++;
        }
    }

    for(i=0;i<used_objects;i++)
    {
        glPushMatrix();
            bind_texture( i );
            //Move to offset
            glTranslatef( objects[i].position_x, objects[i].position_y, 0 );
            glBegin( GL_QUADS );
            //Draw player
                glTexCoord2f( 0.0f, 0.0f ); glVertex2f(                0,                0 );
                glTexCoord2f( 1.0f, 0.0f ); glVertex2f( objects[i].size_x,                0 );
                glTexCoord2f( 1.0f, 1.0f ); glVertex2f( objects[i].size_x, objects[i].size_y );
                glTexCoord2f( 0.0f, 1.0f ); glVertex2f(                0, objects[i].size_y );

            glEnd();

        glPopMatrix();
    }
    glPushMatrix();
            //Move to offset
        glBindTexture(GL_TEXTURE_2D, texture.gui);
        glTranslatef( 0, screen_max_y - GUI_HEIGHT, 0 );
        glBegin( GL_QUADS );
        //Draw player
            glTexCoord2f(0.0f, 0.0f); glVertex2f(            0,          0 );
            glTexCoord2f(1.0f, 0.0f); glVertex2f( screen_max_x,          0 );
            glTexCoord2f(1.0f, 1.0f); glVertex2f( screen_max_x, GUI_HEIGHT );
            glTexCoord2f(0.0f, 1.0f); glVertex2f(            0, GUI_HEIGHT );

        glEnd();

    glPopMatrix();

    glLoadIdentity();

}

/*
 * Author: Robin
 * Description: Frees the texture from the ram so we wont have any memory leaking
 *
 */
void clean_up_editor( textures *texture )
{
    glDeleteTextures(1,&texture->couch);
    glDeleteTextures(1,&texture->gui);
}
#endif
