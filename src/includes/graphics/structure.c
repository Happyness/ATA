#include "structure.h"

#ifndef _C_STRUCTURE
#define _C_STRUCTURE

char * getMapFile(int i)
{
	printf("Try to get map number %d\n", i);
	
	if (i > 0 && i <= 3) {
		char * filename = malloc(sizeof(char) * 30);
		sprintf(filename, "levels/map%d.dat", i);
	
		return filename;
	} else {
		perror("Invalid map number\n");
		exit(1);
	}
}

void mapSave(world * gameWorld, int no)
{
	FILE *save_map;

	printf("saving map\n");

	save_map = fopen(getMapFile(no), "wb");
	fwrite(&gameWorld->objects, sizeof(object), NO_OBJECTS, save_map);
	fclose(save_map);
}

int mapLoad(world * gameWorld, int no)
{
	FILE *load_map;

	printf("Loading map\n");

	load_map = fopen(getMapFile(no), "rb");
	fread(gameWorld->objects, sizeof(object), NO_OBJECTS, load_map);
	fclose(load_map);

	int i;
	for(i = 0; i < NO_OBJECTS; i++)
	{
		if (gameWorld->objects[i].property == 0)
		{
			return i - 1;
		}
	}
}
#endif
