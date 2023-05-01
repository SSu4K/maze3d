#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "level.h"

static const SDL_Color BLUE = {0, 0, 255};
static const SDL_Color DARK_BLUE = {0, 0, 150};
static const SDL_Color DARK_VIOLET = {50, 0, 100};

level_t* new_level(size_t map_width, size_t map_height, int block_width, int block_height){
    level_t* new_level=malloc(sizeof(level_t));
    new_level->map_width = map_width;
    new_level->map_height = map_height;
    new_level->block_width = block_width;
    new_level->block_height = block_height;
    new_level->block_color_1=BLUE;
    new_level->block_color_2=DARK_BLUE;
    new_level->ground_color=DARK_VIOLET;

    new_level->map = calloc(map_width, sizeof(int*));
    for(int x=0;x<map_width;x++){
        new_level->map[x] = calloc(map_height, sizeof(int));
        for(int y=0;y<map_width;y++){
            new_level->map[x][y]=0;
            
        }    
    }
    return new_level;
}

level_t* new_rand_level(size_t map_width, size_t map_height, int block_width, int block_height, float propability){
    level_t* level=new_level(map_width, map_height, block_width, block_height);
    srand(time(NULL));

    for(int x=0;x<map_width;x++){
        for(int y=0;y<map_width;y++){
            if(rand()%100<propability*100){
                level->map[x][y]=1;
            }
        }    
    }
    return level;
}

void free_level(level_t* level){
    for(int x=0;x<level->map_width;x++){
        free(level->map[x]);    
    }
    free(level->map);
    free(level);
}

bool is_in_bound(double x, double y, level_t* level)
{
    if (x < 0 || y < 0 || x >= level->map_width * level->block_width || y >= level->map_height * level->block_width)
    {
        return 0;
    }
    return 1;
}

int get_block_color(double x, double y, level_t* level)
{
    if (!is_in_bound(x, y, level))
        return 0;

    int mx = floor(x / level->block_width);
    int my = floor(y / level->block_width);
    int **ptr1 = level->map;
    ptr1+=mx;
    int *ptr2=*ptr1;
    ptr2+=my;
    return *ptr2;
}