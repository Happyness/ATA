#ifndef _C_MENU
#define _C_MENU

#include "menu.h"

menu meny;

int load_menu(char *background, char *play, char *options, char *editor, char *exit, char *back, int screen_max_x, int screen_max_y )
{
	printf("Before inside load_menu %s, %s, %s, %s, %s\n", background, play, options, editor, exit);

    meny.butText.menu_bg_texture = load_imageRGBA(background);
    meny.butText.button_play 	 = load_imageRGBA(play);
    meny.butText.button_options  = load_imageRGBA(options);
    meny.butText.button_editor   = load_imageRGBA(editor);
    meny.butText.button_exit     = load_imageRGBA(exit);
    meny.butText.button_back     = load_imageRGBA(back);

    printf("After loaded images\n");

    meny.x_play     = (screen_max_x - BUTTON_WIDTH) / 2;
    meny.y_play     = (screen_max_y - BUTTON_HEIGHT) *1/2;
    meny.x_options  = (screen_max_x - BUTTON_WIDTH) / 2;
    meny.y_options  = ((screen_max_y - BUTTON_HEIGHT) *1/2)+BUTTON_HEIGHT + 10;
    meny.x_editor   = (screen_max_x - BUTTON_WIDTH) / 2;
    meny.y_editor   = ((screen_max_y - BUTTON_HEIGHT) *1/2)+BUTTON_HEIGHT*2 + 20;
    meny.x_exit     = (screen_max_x - BUTTON_WIDTH) / 2;
    meny.y_exit     = ((screen_max_y - BUTTON_HEIGHT) *1/2)+BUTTON_HEIGHT*3 + 30;
}

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

//  ***********IMPORTANT************
//  maybe use much CPU power. !!still in testing!!
void mouse_over_menu(int mouse_x, int mouse_y)
{
    int mouse_over_button;
    mouse_over_button = check_menu( mouse_x, mouse_y );

    if( mouse_over_button == 1 )
    {
        meny.butText.button_play = load_imageRGBA("menu/play_activ.png");
    }
    else if( mouse_over_button == 2 )
    {
        meny.butText.button_options = load_imageRGBA("menu/options_activ.png");
    }
    else if( mouse_over_button == 3 )
    {
        meny.butText.button_editor = load_imageRGBA("menu/editor_activ.png");
    }
    else if( mouse_over_button == 4 )
    {
        meny.butText.button_exit = load_imageRGBA("menu/exit_activ.png");
    }
    else
    {
        meny.butText.button_play = load_imageRGBA("menu/play_inactiv.png");
        meny.butText.button_options = load_imageRGBA("menu/options_inactiv.png");
        meny.butText.button_editor = load_imageRGBA("menu/editor_inactiv.png");
        meny.butText.button_exit = load_imageRGBA("menu/exit_inactiv.png");
    }
}

int mouse_down_menu( int mouse_x, int mouse_y )
{
    int mouse_over_button;
    mouse_over_button = check_menu( mouse_x, mouse_y );

    if( mouse_over_button == 1 )
    {
        meny.butText.button_play = load_imageRGBA("menu/play_pressed.png");
    }
    else if( mouse_over_button == 2 )
    {
        meny.butText.button_options = load_imageRGBA("menu/options_pressed.png");
    }
    else if( mouse_over_button == 3 )
    {
        meny.butText.button_editor = load_imageRGBA("menu/editor_pressed.png");
    }
    else if( mouse_over_button == 4 )
    {
        meny.butText.button_exit = load_imageRGBA("menu/exit_pressed.png");
    }
    else
    {
        meny.butText.button_play = load_imageRGBA("menu/play_inactiv.png");
        meny.butText.button_options = load_imageRGBA("menu/options_inactiv.png");
        meny.butText.button_editor = load_imageRGBA("menu/editor_inactiv.png");
        meny.butText.button_exit = load_imageRGBA("menu/exit_inactiv.png");
    }
    return 1;
}

int press_menu(int mouse_x, int mouse_y)
{
    int mouse_over_button;
    mouse_over_button = check_menu( mouse_x, mouse_y );

    if( mouse_over_button == 1 )
    {
	    printf("Trying to play\n");
        return 1;
    }
    else if( mouse_over_button == 2 )
    {
        return 2;
    }
    else if( mouse_over_button == 3 )
    {
        return 3;
    }
    else if( mouse_over_button == 4 )
    {
        return 4;
    }
    else
    {
        meny.butText.button_play = load_imageRGBA("menu/play_inactiv.png");
        meny.butText.button_options = load_imageRGBA("menu/options_inactiv.png");
        meny.butText.button_editor = load_imageRGBA("menu/editor_inactiv.png");
        meny.butText.button_exit = load_imageRGBA("menu/exit_inactiv.png");
    }
    return 0;
}

int check_options(int mouse_x, int mouse_y)
{
    if( ((mouse_x > (800-250)/2) && (mouse_x < ((800-250)/2)+250)) && ( (mouse_y > 600/2) && (mouse_y < (600/2) + 15) ))
    {
        return 1;
    }
    else if( ((mouse_x > (800-200)/2) && (mouse_x < ((800-200)/2)+200)) && ( ( mouse_y > 500) && ( mouse_y < 550) ))
    {
        printf("check options Försöker bryta ut ur options\n");
        return 2;
    }
    else
        return 0;
}

void mouse_over_options(int mouse_x, int mouse_y)
{
    int menu_point = check_options(mouse_x, mouse_y);

    if( menu_point == 2 )
    {
        meny.butText.button_back = load_imageRGBA("menu/back_activ.png");
    }
    else

        meny.butText.button_back = load_imageRGBA("menu/back_inactiv.png");
}

int press_options(int mouse_x, int mouse_y)
{
    int mouse_over_button;
    mouse_over_button = check_options( mouse_x, mouse_y );

    if( mouse_over_button == 1 )
    {
        printf("Enter typemode for IP field\n");
        return 1;
    }
    else if( mouse_over_button == 2 )
    {
        meny.butText.button_back = load_imageRGBA("menu/back_pressed.png");
        printf("press optionsFörsöker bryta ut ur options\n");
        return 2;
    }
    else
    {
        meny.butText.button_back = load_imageRGBA("menu/back_inactiv.png");
        return 0;
    }
}

void handle_input(SDL_Event event, char str[])
{
  int size = 16;
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( strlen(str) != 0 ) )
        {
            //Remove a character from the end
            printf("string lenght %d %c\n",strlen(str), str[strlen(str)-1]);
            str[strlen(str)-1] = 0;
        }
        //If the string less than maximum size
        else if( (strlen(str) < size) && ( event.key.keysym.sym != SDLK_BACKSPACE) && ( event.key.keysym.sym != SDLK_ESCAPE) && ( event.key.keysym.sym != SDLK_RETURN))
        {
            sprintf(str,"%s%c",str,event.key.keysym.sym);
            str[strlen(str)] = 0;
        }

    }
}
void drawBack()
{
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, meny.butText.button_back);
        glTranslatef( (800 - 200)/2, 500, 0 );
        glBegin( GL_QUADS );
            //Draw options
            glTexCoord2f(0.0f, 0.0f); glVertex2f(   0,  0);
            glTexCoord2f(1.0f, 0.0f); glVertex2f( 200,  0);
            glTexCoord2f(1.0f, 1.0f); glVertex2f( 200, 50);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(   0, 50);
        glEnd();
    glPopMatrix();
}
void drawMenu(int screen_max_x, int screen_max_y)
{
    //Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );
     //Move to offset
    glTranslatef( 0, 0, 0 );

    glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, meny.butText.menu_bg_texture);
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

        glBindTexture(GL_TEXTURE_2D, meny.butText.button_play);
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
        glBindTexture(GL_TEXTURE_2D, meny.butText.button_options);
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
        glBindTexture(GL_TEXTURE_2D, meny.butText.button_editor);
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
        glBindTexture(GL_TEXTURE_2D, meny.butText.button_exit);
        glTranslatef( meny.x_exit, meny.y_exit, 0 );
        glBegin( GL_QUADS );
            //Draw player
            glTexCoord2f(0.0f, 0.0f); glVertex3f(            0,             0, 0 );
            glTexCoord2f(1.0f, 0.0f); glVertex3f( BUTTON_WIDTH,             0, 0 );
            glTexCoord2f(1.0f, 1.0f); glVertex3f( BUTTON_WIDTH, BUTTON_HEIGHT, 0 );
            glTexCoord2f(0.0f, 1.0f); glVertex3f(            0, BUTTON_HEIGHT, 0 );

        glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, (GLuint)NULL);

    //Reset
    glLoadIdentity();
    //Update screen
    SDL_GL_SwapBuffers();
}

void clean_up_menu()
{
    glDeleteTextures(1,&meny.butText.menu_bg_texture);
    glDeleteTextures(1,&meny.butText.button_play);
    glDeleteTextures(1,&meny.butText.button_options);
    glDeleteTextures(1,&meny.butText.button_editor);
    glDeleteTextures(1,&meny.butText.button_exit);
}

#endif
