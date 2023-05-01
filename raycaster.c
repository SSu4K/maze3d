#include "raycaster.h"
#include "level.h"

#define RAY_MIN_STEP 0.3
#define RAY_MAX_STEP 3.0
#define RAY_STEP_T 300.0

static const SDL_Color BLACK = {0, 0, 0};


ray_t *new_ray(double start_x, double start_y, double screen_x, double screen_y)
{
    ray_t *new_ray = malloc(sizeof(ray_t));
    double dd = 1;
    double dx = screen_x - start_x;
    double dy = screen_y - start_y;
    double d = dd / sqrt(pow(dx, 2) + pow(dy, 2));

    new_ray->start_x = start_x;
    new_ray->start_y = start_y;
    new_ray->dl = dd;
    new_ray->dx = dx * d;
    new_ray->dy = dy * d;
    new_ray->length = 0;
    new_ray->color = BLACK;
    return new_ray;
}

float get_ray_step(float distance){
    return RAY_MAX_STEP + (RAY_MIN_STEP-RAY_MAX_STEP)*exp((-1)/RAY_STEP_T*distance);
}

void ray_cast(ray_t *ray, level_t* level)
{
    double x = ray->start_x;
    double y = ray->start_y;
    while (is_in_bound(x, y, level))
    {
        double step = get_ray_step(ray->length);
        x += ray->dx*step;
        y += ray->dy*step;
        ray->length += step;
        if (get_block_color(x, y, level) == 1)
        {
            if (abs(fmod(x, level->block_width)-level->block_width/2) > abs(fmod(y, level->block_width)-level->block_width/2))
            {   
                
                ray->color = level->block_color_1;
                
                
            }
            else
            {
                ray->color = level->block_color_2;
            }
            return;
        }
    }
    ray->length=0;
    return;
}