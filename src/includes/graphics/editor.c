#ifndef _C_EDITOR
#define _C_EDITOR

#include "editor.h"

textures texture;

void init_editor(world * gameWorld)
{

    char * couch  = "object/soffa.png";
	char * wall   = "object/wall.png";
	char * floor  = "object/floor.png";
	char * table  = "object/table.png";
	char * stair  = "object/stair.png";
	char * fence  = "object/fence.png";
	char * box    = "object/box.png";
	char * finish = "object/finish.png";
	char * start  = "object/start.png";


	printf("before Load images\n");

	texture.couch = load_imageRGBA(couch);
	texture.wall = load_imageRGBA(wall);
	texture.floor = load_imageRGBA(floor);
	texture.table = load_imageRGBA(table);
	texture.stair = load_imageRGBA(stair);
	texture.fence = load_imageRGBA(fence);
	texture.box = load_imageRGBA(box);
	texture.finish = load_imageRGBA(finish);
	texture.start = load_imageRGBA(start);

	printf("After load images\n");
	int i;

	for (i=0;i<NO_OBJECTS;i++) {
	    gameWorld->objects[i].id = 0;
		gameWorld->objects[i].property = 0;
		gameWorld->objects[i].movable = 0;
		gameWorld->objects[i].box.x = 0;
		gameWorld->objects[i].box.y = 0;
		gameWorld->objects[i].box.width = 0;
		gameWorld->objects[i].box.height = 0;
		gameWorld->objects[i].box.dx = BOX_DX;
		gameWorld->objects[i].box.dy = BOX_DY;
	}
}

void editor_undo(int latest_object, world * gameWorld)
{
    gameWorld->objects[latest_object].id = 0;
    gameWorld->objects[latest_object].property = 0;
    gameWorld->objects[latest_object].movable = 0;
    gameWorld->objects[latest_object].box.x = 0;
    gameWorld->objects[latest_object].box.y = 0;
    gameWorld->objects[latest_object].box.width = 0;
    gameWorld->objects[latest_object].box.height = 0;
    gameWorld->objects[latest_object].box.dx = BOX_DX;
    gameWorld->objects[latest_object].box.dy = BOX_DY;
}

void editor_create_object( int mouse_x, int mouse_y, int property, int *free_struct_space ,world * gameWorld)
{
    int i;
    for(i=2;i<NO_OBJECTS;i++)
    {
        if(gameWorld->objects[i].property == 0)
        {
            *free_struct_space = i;
            break;
        }
    }
    switch(property)
    {
        //couch
        case 1:
            gameWorld->objects[*free_struct_space].id = *free_struct_space;
            gameWorld->objects[*free_struct_space].property = property;
            gameWorld->objects[*free_struct_space].movable = 0;
            gameWorld->objects[*free_struct_space].box.width = 40;
            gameWorld->objects[*free_struct_space].box.height = 14;
            gameWorld->objects[*free_struct_space].box.x = mouse_x - (gameWorld->objects[*free_struct_space].box.width / 2);
            gameWorld->objects[*free_struct_space].box.y = mouse_y - (gameWorld->objects[*free_struct_space].box.height / 2);
            gameWorld->objects[*free_struct_space].box.dx = BOX_DX;
            gameWorld->objects[*free_struct_space].box.dy = BOX_DY;
            break;
        //floor
        case 2:
            gameWorld->objects[*free_struct_space].id = *free_struct_space;
            gameWorld->objects[*free_struct_space].property = property;
            gameWorld->objects[*free_struct_space].movable = 0;
            gameWorld->objects[*free_struct_space].box.width = 200;
            gameWorld->objects[*free_struct_space].box.height = 15;
            gameWorld->objects[*free_struct_space].box.x = mouse_x - (gameWorld->objects[*free_struct_space].box.width / 2);
            gameWorld->objects[*free_struct_space].box.y = mouse_y - (gameWorld->objects[*free_struct_space].box.height / 2);
            gameWorld->objects[*free_struct_space].box.dx = BOX_DX;
            gameWorld->objects[*free_struct_space].box.dy = BOX_DY;
            break;
        //wall
        case 3:
            gameWorld->objects[*free_struct_space].id = *free_struct_space;
            gameWorld->objects[*free_struct_space].property = property;
            gameWorld->objects[*free_struct_space].movable = 0;
            gameWorld->objects[*free_struct_space].box.width = 15;
            gameWorld->objects[*free_struct_space].box.height = 200;
            gameWorld->objects[*free_struct_space].box.x = mouse_x - (gameWorld->objects[*free_struct_space].box.width / 2);
            gameWorld->objects[*free_struct_space].box.y = mouse_y - (gameWorld->objects[*free_struct_space].box.height / 2);
            gameWorld->objects[*free_struct_space].box.dx = BOX_DX;
            gameWorld->objects[*free_struct_space].box.dy = BOX_DY;
            break;
        //stair
        case 4:
            gameWorld->objects[*free_struct_space].id = *free_struct_space;
            gameWorld->objects[*free_struct_space].property = property;
            gameWorld->objects[*free_struct_space].movable = 0;
            gameWorld->objects[*free_struct_space].box.width = 40;
            gameWorld->objects[*free_struct_space].box.height = 14;
            gameWorld->objects[*free_struct_space].box.x = mouse_x - (gameWorld->objects[*free_struct_space].box.width / 2);
            gameWorld->objects[*free_struct_space].box.y = mouse_y - (gameWorld->objects[*free_struct_space].box.height / 2);
            gameWorld->objects[*free_struct_space].box.dx = BOX_DX;
            gameWorld->objects[*free_struct_space].box.dy = BOX_DY;
            break;
        //fence
        case 5:
            gameWorld->objects[*free_struct_space].id = *free_struct_space;
            gameWorld->objects[*free_struct_space].property = property;
            gameWorld->objects[*free_struct_space].movable = 0;
            gameWorld->objects[*free_struct_space].box.width = 40;
            gameWorld->objects[*free_struct_space].box.height = 20;
            gameWorld->objects[*free_struct_space].box.x = mouse_x - (gameWorld->objects[*free_struct_space].box.width / 2);
            gameWorld->objects[*free_struct_space].box.y = mouse_y - (gameWorld->objects[*free_struct_space].box.height / 2);
            gameWorld->objects[*free_struct_space].box.dx = BOX_DX;
            gameWorld->objects[*free_struct_space].box.dy = BOX_DY;
            break;
        //table
        case 6:
            gameWorld->objects[*free_struct_space].id = *free_struct_space;
            gameWorld->objects[*free_struct_space].property = property;
            gameWorld->objects[*free_struct_space].movable = 0;
            gameWorld->objects[*free_struct_space].box.width = 40;
            gameWorld->objects[*free_struct_space].box.height = 10;
            gameWorld->objects[*free_struct_space].box.x = mouse_x - (gameWorld->objects[*free_struct_space].box.width / 2);
            gameWorld->objects[*free_struct_space].box.y = mouse_y - (gameWorld->objects[*free_struct_space].box.height / 2);
            gameWorld->objects[*free_struct_space].box.dx = BOX_DX;
            gameWorld->objects[*free_struct_space].box.dy = BOX_DY;
            break;
        //box
        case 7:
            gameWorld->objects[*free_struct_space].id = *free_struct_space;
            gameWorld->objects[*free_struct_space].property = property;
            gameWorld->objects[*free_struct_space].movable = 1;
            gameWorld->objects[*free_struct_space].box.width = 50;
            gameWorld->objects[*free_struct_space].box.height = 50;
            gameWorld->objects[*free_struct_space].box.x = mouse_x - (gameWorld->objects[*free_struct_space].box.width / 2);
            gameWorld->objects[*free_struct_space].box.y = mouse_y - (gameWorld->objects[*free_struct_space].box.height / 2);
            gameWorld->objects[*free_struct_space].box.dx = BOX_DX;
            gameWorld->objects[*free_struct_space].box.dy = BOX_DY;
            break;
        //movable wall
        case 8:
            gameWorld->objects[*free_struct_space].id = *free_struct_space;
            gameWorld->objects[*free_struct_space].property = property;
            gameWorld->objects[*free_struct_space].movable = 1;
            gameWorld->objects[*free_struct_space].box.width = 15;
            gameWorld->objects[*free_struct_space].box.height = 200;
            gameWorld->objects[*free_struct_space].box.x = mouse_x - (gameWorld->objects[*free_struct_space].box.width / 2);
            gameWorld->objects[*free_struct_space].box.y = mouse_y - (gameWorld->objects[*free_struct_space].box.height / 2);
            gameWorld->objects[*free_struct_space].box.dx = BOX_DX;
            gameWorld->objects[*free_struct_space].box.dy = BOX_DY;
            break;
        //start point
        case 's':
            gameWorld->objects[0].id = 0;
            gameWorld->objects[0].property = property;
            gameWorld->objects[0].movable = 0;
            gameWorld->objects[0].box.width = PLAYER_WIDTH;
            gameWorld->objects[0].box.height = PLAYER_HEIGHT;
            gameWorld->objects[0].box.x = mouse_x - (gameWorld->objects[0].box.width / 2);
            gameWorld->objects[0].box.y = mouse_y - (gameWorld->objects[0].box.height / 2);
            break;
        //Finish line
        case 'e':
            gameWorld->objects[1].id = 1;
            gameWorld->objects[1].property = property;
            gameWorld->objects[1].movable  = 0;
            gameWorld->objects[1].box.width = PLAYER_WIDTH;
            gameWorld->objects[1].box.height = PLAYER_HEIGHT;
            gameWorld->objects[1].box.x = mouse_x - (gameWorld->objects[1].box.width / 2);
            gameWorld->objects[1].box.y = mouse_y - (gameWorld->objects[1].box.height / 2);
            break;
        default:
            break;
    }
}

void editor_start_move_object( int mouse_x, int mouse_y, int *old_mouse_x, int *old_mouse_y )
{
    *old_mouse_x = mouse_x;
    *old_mouse_y = mouse_y;
}

void editor_update_move_object( int mouse_x, int mouse_y, int *old_mouse_x, int *old_mouse_y , world * gameWorld)
{
    int i;
    for(i=NO_OBJECTS-1;i>=0;i--)
    {
        if( (mouse_x > gameWorld->objects[i].box.x) && (mouse_x < gameWorld->objects[i].box.x + gameWorld->objects[i].box.width) )
        {
            if( (mouse_y > gameWorld->objects[i].box.y) && (mouse_y < gameWorld->objects[i].box.y + gameWorld->objects[i].box.height) )
            {
                gameWorld->objects[i].box.x += mouse_x - *old_mouse_x;
                gameWorld->objects[i].box.y += mouse_y - *old_mouse_y;
                break;
            }
        }
    }
    *old_mouse_x = mouse_x;
    *old_mouse_y = mouse_y;
}

void bind_texture(int object_id,world * gameWorld)
{
    switch(gameWorld->objects[object_id].property)
    {
        case 1:
            glBindTexture(GL_TEXTURE_2D, texture.couch);
            break;
        case 2:
            glBindTexture(GL_TEXTURE_2D, texture.floor);
            break;
        case 3:
            glBindTexture(GL_TEXTURE_2D, texture.wall);
            break;
        case 4:
            glBindTexture(GL_TEXTURE_2D, texture.stair);
            break;
        case 5:
            glBindTexture(GL_TEXTURE_2D, texture.fence);
            break;
        case 6:
            glBindTexture(GL_TEXTURE_2D, texture.table);
            break;
        case 7:
            glBindTexture(GL_TEXTURE_2D, texture.box);
            break;
        case 8:
            glBindTexture(GL_TEXTURE_2D, texture.wall);
            break;
        case 's':
            glBindTexture(GL_TEXTURE_2D, texture.start);
            break;
        case 'e':
            glBindTexture(GL_TEXTURE_2D, texture.finish);
            break;
        default:
            glBindTexture(GL_TEXTURE_2D, (GLuint)NULL);
            break;
    }
    //glBindTexture(GL_TEXTURE_2D, object[i].object_texture);
}

void editor_show(int screen_max_x, int screen_max_y,world *gameWorld)
{
    //Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );
    glTranslatef(0,0,0);
    int i,j,used_objects = 0;

    for(j=0; j<NO_OBJECTS;j++)
    {
        if(gameWorld->objects[j].property == 0)
            break;
        else
            used_objects++;
    }

    for(i=0;i<used_objects;i++)
    {
        glPushMatrix();
            bind_texture(i,gameWorld);
            //move to offset
            glTranslatef(gameWorld->objects[i].box.x,gameWorld->objects[i].box.y,0);
            glBegin( GL_QUADS );
                glTexCoord2f(0,0); glVertex2f(                              0,                     0);
                glTexCoord2f(1,0); glVertex2f(gameWorld->objects[i].box.width,                     0);
                glTexCoord2f(1,1); glVertex2f(gameWorld->objects[i].box.width, gameWorld->objects[i].box.height);
                glTexCoord2f(0,1); glVertex2f(                              0, gameWorld->objects[i].box.height);
            glEnd();
        glPopMatrix();
    }
    glLoadIdentity();
    //Update screen
    SDL_GL_SwapBuffers();
}

void clean_up_editor()
{
    glDeleteTextures(1,&texture.couch);
    glDeleteTextures(1,&texture.wall);
    glDeleteTextures(1,&texture.floor);
    glDeleteTextures(1,&texture.table);
    glDeleteTextures(1,&texture.stair);
    glDeleteTextures(1,&texture.fence);
    glDeleteTextures(1,&texture.box);

}
#endif
