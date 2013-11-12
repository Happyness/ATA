#ifndef _H_MENU
#define _H_MENU

#define BUTTON_HEIGHT 50
#define BUTTON_WIDTH 200

typedef struct
{
    GLuint menu_bg_texture;
    GLuint button_play;
    GLuint button_options;
    GLuint button_editor;
    GLuint button_exit;
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

menu meny;

void load_menu( char *background, char *play, char *options, char *editor, char *exit, int screen_maxX, int screen_maxY);

int check_menu( int mouse_x, int mouse_y );

void mouse_over_menu( int mouse_x, int mouse_y );

int mouse_down_menu( int mouse_x, int mouse_y );

int press_menu( int mouse_x, int mouse_y );

void show_menu( int screen_max_x, int screen_max_y );

void clean_up_menu();



#endif // MENU_H_INCLUDED
