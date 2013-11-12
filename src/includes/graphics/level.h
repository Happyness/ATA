#ifndef _H_LEVEL
#define _H_LEVEL

struct level_t3
{
    GLuint bg_texture;
    int width;
    int height;
};

void load_level(struct level_t3 * level, char *background);

void show_level(struct level_t3 * level, int screen_max_x,int screen_max_y);


#endif // _H_LEVEL
