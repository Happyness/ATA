#ifndef _C_MENU
#define _C_MENU

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "menu.h"


/*
 * Author: Robin & Sarah
 * Description: Initializing the buttons, backgrounds, offset..etc..
 *
 */
void load_menu(char *background, char *play, char *options, char *editor, char *exit, int screen_max_x, int screen_max_y )
{
	printf("Before inside load_menu %s, %s, %s, %s, %s\n", background, play, options, editor, exit);
	
    meny.menu_bg_texture = load_imageRGBA(background);
    meny.button_play 	  = load_imageRGBA(play);
    meny.button_options = load_imageRGBA(options);
    meny.button_editor = load_imageRGBA(editor);
    meny.button_exit = load_imageRGBA(exit);
    
    printf("After loaded images\n");
    
    meny.x_play = (screen_max_x - BUTTON_WIDTH) / 2;
    meny.y_play = 100;
    meny.x_options = (screen_max_x - BUTTON_WIDTH) / 2;
    meny.y_options = 200;
    meny.x_editor = (screen_max_x - BUTTON_WIDTH) / 2;
    meny.y_editor = 300;
    meny.x_exit = (screen_max_x - BUTTON_WIDTH) / 2;
    meny.y_exit = 400;
}
/*
 * Author: Robin & Sarah
 * Description: Checks positioning for the mouse compared to buttons
 *
 */
int check_menu(int mouse_x, int mouse_y)
{
    if( (mouse_x > meny.x_play) && (mouse_x < meny.x_play + BUTTON_WIDTH) )
    {
        if( (mouse_y > meny.y_play) && (mouse_y < meny.y_play + BUTTON_HEIGHT) )
        {
            return 1;
        }
    }
    if( (mouse_x > meny.x_options) && (mouse_x < meny.x_options + BUTTON_WIDTH) )
    {
        if( (mouse_y > meny.y_options) && (mouse_y < meny.y_options + BUTTON_HEIGHT) )
        {
            return 2;
        }
    }
    if( (mouse_x > meny.x_editor) && (mouse_x < meny.x_editor + BUTTON_WIDTH) )
    {
        if( (mouse_y > meny.y_editor) && (mouse_y < meny.y_editor + BUTTON_HEIGHT) )
        {
            return 3;
        }
    }
    if( (mouse_x > meny.x_exit) && (mouse_x < meny.x_exit + BUTTON_WIDTH) )
    {
        if( (mouse_y > meny.y_exit) && (mouse_y < meny.y_exit + BUTTON_HEIGHT) )
        {
            return 4;
        }
    }

    //Else
    return 0;
}

/*
 * Author: Robin & Sarah
 * Description: Switches texture on button while hovering the mouse over it.
 *
 */
//  ***********IMPORTANT************
//  maybe use much CPU power. !!still in testing!!
void mouse_over_menu(int mouse_x, int mouse_y)
{
    int mouse_over_button;
    mouse_over_button = check_menu( mouse_x, mouse_y );
    
    printf("Before load image in mouse over menu, %d\n", mouse_over_button);

    if( mouse_over_button == 1 )
    {
        //meny.button_play = load_imageRGBA("play_activ.png");
    }
    else if( mouse_over_button == 2 )
    {
        //meny.button_options = load_imageRGBA("options_activ.png");
    }
    else if( mouse_over_button == 3 )
    {
        //meny.button_editor = load_imageRGBA("editor_activ.png");
    }
    else if( mouse_over_button == 4 )
    {
        //meny.button_exit = load_imageRGBA("exit_activ.png");
    }
    else
    {
	    printf("Before load inactive images\n");
        //meny.button_play = load_imageRGBA("play_inactiv.png");
        //meny.button_options = load_imageRGBA("options_inactiv.png");
        //meny.button_editor = load_imageRGBA("editor_inactiv.png");
        //meny.button_exit = load_imageRGBA("exit_inactiv.png");
    }
}

/*
 * Author: Robin
 * Description: Switches texture on button while clicking the mouse on it.
 *
 */
int mouse_down_menu( int mouse_x, int mouse_y )
{
    int mouse_over_button;
    mouse_over_button = check_menu( mouse_x, mouse_y );

    if( mouse_over_button == 1 )
    {
        //meny.button_play = load_imageRGBA("play_pressed.png");
    }
    else if( mouse_over_button == 2 )
    {
        //meny.button_options = load_imageRGBA("options_pressed.png");
    }
    else if( mouse_over_button == 3 )
    {
        //meny.button_editor = load_imageRGBA("editor_pressed.png");
    }
    else if( mouse_over_button == 4 )
    {
        //meny.button_exit = load_imageRGBA("exit_pressed.png");
    }
    else
    {
        //meny.button_play = load_imageRGBA("play_inactiv.png");
        //meny.button_options = load_imageRGBA("options_inactiv.png");
        //meny.button_editor = load_imageRGBA("editor_inactiv.png");
        //meny.button_exit = load_imageRGBA("exit_inactiv.png");
    }
    return 1;
}

/*
 * Author: Sarah
 * Description: checks if any button was pressed and continues from the users option.
 *
 */
int press_menu(int mouse_x, int mouse_y)
{
    int mouse_over_button;
    mouse_over_button = check_menu( mouse_x, mouse_y );

    if( mouse_over_button == 1 )
    {
	    printf("Try to play\n");
        playing();
    }
    else if( mouse_over_button == 2 )
    {
        //options();
    }
    else if( mouse_over_button == 3 )
    {
        in_editor();
    }
    else if( mouse_over_button == 4 )
    {
        clean_up();
        exit(0);
    }
    else
    {
        //meny.button_play = load_imageRGBA("play_inactiv.png");
        //meny.button_options = load_imageRGBA("options_inactiv.png");
        //meny.button_editor = load_imageRGBA("editor_inactiv.png");
        //meny.button_exit = load_imageRGBA("exit_inactiv.png");
    }
    return 0;
}

/*
 * Author: Robin & Sarah
 * Description: Draw the menu using boxes starting with background and working to the top layers.
 *
 */
void show_menu(int screen_max_x, int screen_max_y)
{
     //Move to offset
    glTranslatef( 0, 0, 0 );

    glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, meny.menu_bg_texture);
        glTranslatef(0,0,0);
        glBegin( GL_QUADS );
            //Draw player
            glTexCoord2f(0.0f, 0.0f); glVertex3f(            0,             0, 0 );
            glTexCoord2f(1.0f, 0.0f); glVertex3f( screen_max_x,             0, 0 );
            glTexCoord2f(1.0f, 1.0f); glVertex3f( screen_max_x, screen_max_y, 0 );
            glTexCoord2f(0.0f, 1.0f); glVertex3f(            0, screen_max_y, 0 );

        glEnd();
    glPopMatrix();

    glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, meny.button_play);
        glTranslatef( meny.x_play, meny.y_play, 0 );
        glBegin( GL_QUADS );
            //Draw player
            glTexCoord2f(0.0f, 0.0f); glVertex3f(            0,             0, 0 );
            glTexCoord2f(1.0f, 0.0f); glVertex3f( BUTTON_WIDTH,             0, 0 );
            glTexCoord2f(1.0f, 1.0f); glVertex3f( BUTTON_WIDTH, BUTTON_HEIGHT, 0 );
            glTexCoord2f(0.0f, 1.0f); glVertex3f(            0, BUTTON_HEIGHT, 0 );

        glEnd();
    glPopMatrix();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, meny.button_options);
        glTranslatef( meny.x_options, meny.y_options, 0 );
        glBegin( GL_QUADS );
            //Draw player
            glTexCoord2f(0.0f, 0.0f); glVertex3f(            0,             0, 0 );
            glTexCoord2f(1.0f, 0.0f); glVertex3f( BUTTON_WIDTH,             0, 0 );
            glTexCoord2f(1.0f, 1.0f); glVertex3f( BUTTON_WIDTH, BUTTON_HEIGHT, 0 );
            glTexCoord2f(0.0f, 1.0f); glVertex3f(            0, BUTTON_HEIGHT, 0 );

        glEnd();
    glPopMatrix();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, meny.button_editor);
        glTranslatef( meny.x_editor, meny.y_editor, 0 );
        glBegin( GL_QUADS );
            //Draw player
            glTexCoord2f(0.0f, 0.0f); glVertex3f(            0,             0, 0 );
            glTexCoord2f(1.0f, 0.0f); glVertex3f( BUTTON_WIDTH,             0, 0 );
            glTexCoord2f(1.0f, 1.0f); glVertex3f( BUTTON_WIDTH, BUTTON_HEIGHT, 0 );
            glTexCoord2f(0.0f, 1.0f); glVertex3f(            0, BUTTON_HEIGHT, 0 );

        glEnd();
    glPopMatrix();


    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, meny.button_exit);
        glTranslatef( meny.x_exit, meny.y_exit, 0 );
        glBegin( GL_QUADS );
            //Draw player
            glTexCoord2f(0.0f, 0.0f); glVertex3f(            0,             0, 0 );
            glTexCoord2f(1.0f, 0.0f); glVertex3f( BUTTON_WIDTH,             0, 0 );
            glTexCoord2f(1.0f, 1.0f); glVertex3f( BUTTON_WIDTH, BUTTON_HEIGHT, 0 );
            glTexCoord2f(0.0f, 1.0f); glVertex3f(            0, BUTTON_HEIGHT, 0 );

        glEnd();
    glPopMatrix();

    //Reset
    glLoadIdentity();
}

/*
 * Author: Robin
 * Description: Frees the texture so we dont have memory leaking..
 *
 */
void clean_up_menu(menu *meny)
{
    glDeleteTextures(1,&meny->menu_bg_texture);
    glDeleteTextures(1,&meny->button_play);
    glDeleteTextures(1,&meny->button_options);
    glDeleteTextures(1,&meny->button_exit);
}

#endif
