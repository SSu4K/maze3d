#ifndef __RAYCASTER_H__
#define __RAYCASTER_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include "level.h"

typedef struct Ray
{
    SDL_Color color;
    double start_x;
    double start_y;
    double dx;
    double dy;
    double dl;
    double length;
} ray_t;

ray_t *new_ray(double start_x, double start_y, double screen_x, double screen_y);
void ray_cast(ray_t *ray, level_t* level);

#endif