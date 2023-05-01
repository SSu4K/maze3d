
#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <SDL2/SDL.h>
#include<stdbool.h>

typedef struct Level
{
    int block_width;
    int block_height;
    size_t map_width;
    size_t map_height;
    SDL_Color block_color_1;
    SDL_Color block_color_2;
    SDL_Color ground_color;
    int **map;
} level_t;

level_t* new_level(size_t map_width, size_t map_height, int block_width, int block_height);
level_t* new_rand_level(size_t map_width, size_t map_height, int block_width, int block_height, float propability);
void free_level(level_t* level);
bool is_in_bound(double x, double y, level_t* level);
int get_block_color(double x, double y, level_t* level);

#endif