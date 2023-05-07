#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "level.h"

static const SDL_Color BLACK = {0, 0, 0};
static const SDL_Color BLUE = {10, 30, 200};
static const SDL_Color DARK_BLUE = {10, 20, 150};
static const SDL_Color DARK_VIOLET = {50, 0, 100};

wall_t* new_wall(double x1, double y1, double x2, double y2, double height, SDL_Color color){
    wall_t* wall = malloc(sizeof(wall_t));
    wall->start_x=x1;
    wall->start_y=y1;
    wall->dx=x2-x1;
    wall->dy=y2-y1;
    wall->height=height;
    wall->color=color;

    return wall;
}

level_t* new_level(size_t map_width, size_t map_height, int block_width, int block_height){
    level_t* new_level=malloc(sizeof(level_t));
    new_level->block_height=block_height;
    new_level->map_width = map_width;
    new_level->map_height = map_height;
    new_level->ground_color=DARK_VIOLET;
    new_level->walls_count=0;
    new_level->walls_list=calloc(0, sizeof(wall_t*));

    return new_level;
}

level_t* new_rand_level(size_t map_width, size_t map_height, int block_width, int block_height, float propability){
    level_t* level=new_level(map_width, map_height, block_width, block_height);
    srand(time(NULL));

    for(int x=0;x<map_width;x+=block_width){
        for(int y=0;y<map_height;y+=block_width){
            if(rand()%100<propability*100){
                level->walls_count+=4;
                level->walls_list = realloc(level->walls_list, level->walls_count*sizeof(wall_t*));
                
                level->walls_list[level->walls_count-1]=new_wall(x, y, x+block_width, y, block_height, DARK_BLUE);
                level->walls_list[level->walls_count-2]=new_wall(x, y+block_width, x+block_width, y+block_width, block_height, DARK_BLUE);
                level->walls_list[level->walls_count-3]=new_wall(x, y, x, y+block_width, block_height, BLUE);
                level->walls_list[level->walls_count-4]=new_wall(x+block_width, y, x+block_width, y+block_width, block_height, BLUE);
            }
        }    
    }
    level->walls_list = realloc(level->walls_list, level->walls_count*sizeof(wall_t*));
    level->walls_list[level->walls_count-1]=new_wall(0, 0, map_width, 0, block_height, BLACK);
    level->walls_list[level->walls_count-1]=new_wall(0, 0, 0, map_height, block_height, BLACK);
    level->walls_list[level->walls_count-1]=new_wall(0, map_height, map_width, map_height, block_height, BLACK);
    level->walls_list[level->walls_count-1]=new_wall(map_width, 0, map_width, map_height, block_height, BLACK);
    return level;
}

void free_level(level_t* level){

    for(int i=0;i<level->walls_count;i++){
        if(level->walls_list[i]!=NULL){
            free(level->walls_list[i]);
        }
    }
    
    free(level->walls_list);
    free(level);
}

bool is_in_bound(double x, double y, level_t* level)
{
    if (x < 0 || y < 0 || x > level->map_width || y > level->map_height)
    {
        return 0;
    }
    return 1;
}