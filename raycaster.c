#include "raycaster.h"
#include "level.h"

#define RAY_MIN_STEP 0.3
#define RAY_MAX_STEP 3.0
#define RAY_STEP_T 300.0

static const SDL_Color BLACK = {0, 0, 0};

ray_t *new_ray(double start_x, double start_y, double screen_x, double screen_y)
{
    ray_t *new_ray = malloc(sizeof(ray_t));
    double dx = screen_x - start_x;
    double dy = screen_y - start_y;
    double d = 1 / sqrt(pow(dx, 2) + pow(dy, 2));

    new_ray->start_x = start_x;
    new_ray->start_y = start_y;
    new_ray->dl = 1;
    new_ray->dx = dx * d;
    new_ray->dy = dy * d;
    new_ray->length = 0;
    new_ray->color = BLACK;
    return new_ray;
}

void ray_cast(ray_t *ray, level_t *level)
{
    double x = ray->start_x;
    double y = ray->start_y;
    double ray_dx = ray->dx;
    double ray_dy = ray->dy;
    for (int i = 0; i < level->walls_count; i++)
    {
        double wall_dx = level->walls_list[i]->dx;
        double wall_dy = level->walls_list[i]->dy;
        double source_dx = x - level->walls_list[i]->start_x;
        double source_dy = y - level->walls_list[i]->start_y;
        
        double D=(wall_dy)*ray_dx-(wall_dx)*ray_dy;
        if(D!=0){
            double k=(source_dy*ray_dx-source_dx*ray_dy)/D;
            if(k>0&&k<1){
                double t = (wall_dx*source_dy-wall_dy*source_dx)/D;
                if(t>=0&&(t<ray->length||ray->length==0)){
                    ray->length=t;
                    ray->color=level->walls_list[i]->color;
                }
            }
        }
    }
}