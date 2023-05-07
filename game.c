#include "renderer.h"
#include "raycaster.h"
#include "game.h"

static const SDL_Color BLACK = {0, 0, 0};

player_t* new_player(double x, double y, double height, double radius, double rotation, double fov, double intensity){
    player_t* player = malloc(sizeof(player_t));
    player->x=x;
    player->y=y;
    player->camera_height=height;
    player->player_radius=radius;
    player->rotation=rotation;
    player->fov=fov;
    player->light_intenstity=intensity;

    return player;
}

void free_game(game_t* game){
    free_level(game->level);
    free(game->player);
}

void draw_view(game_t* game)
{
    int screen_width = window_width();
    int screen_height = window_height();
    ray_t *ray;
    level_t* level = game->level;
    player_t* player = game->player;

    double start_x = player->x;
    double start_y = player->y;
    double camera_height = player->camera_height;
    double player_radius = player->player_radius;
    double rotation = player->rotation;
    double fov = player->fov;

    double screen_x1 = start_x + player_radius * cos(rotation - fov / 2);
    double screen_y1 = start_y + player_radius * sin(rotation - fov / 2);
    double screen_x2 = start_x + player_radius * cos(rotation + fov / 2);
    double screen_y2 = start_y + player_radius * sin(rotation + fov / 2);

    for (int i = 0; i < screen_width; i++)
    {

        double screen_x = (screen_x1 * i + screen_x2 * (screen_width - i)) / screen_width;
        double screen_y = (screen_y1 * i + screen_y2 * (screen_width - i)) / screen_width;
        double d = sqrt(pow((start_x - screen_x), 2) + pow((start_y - screen_y), 2));
        ray = new_ray(start_x, start_y, screen_x, screen_y);
        ray_cast(ray, level);
        double distance = ray->length;
        double brightness = exp((-0.005)*distance);

        if (ray->color.r!=0||ray->color.g!=0||ray->color.b!=0)
        {
            int height1 = d * (level->block_height - camera_height) / distance;
            int height2 = d * camera_height / distance;
            int x=i;
            int y2=screen_height / 2 + height2;
            int y1=screen_height / 2 - height1;
            double d2=pow(distance, 2)+pow(level->block_height - camera_height,2);
            double d1=pow(distance, 2)+pow(camera_height,2);
            double l=pow(level->block_height , 2);
            vertical_shaded_line(x, y1, y2, ray->color, d1, d2, l, player->light_intenstity);
            vertical_line(i, screen_height, screen_height / 2 + height2, level->ground_color);
        }
        else
        {
            vertical_line(i, screen_height, screen_height / 2, level->ground_color);
        }

        free(ray);
    }
}

void run_game(game_t* game){
    renderer_init();
    player_t* player = game->player;
    printf("Started game\n");
    
    while (!is_key_down(SDLK_ESCAPE))
    {
        window_update();

        draw_view(game);
        if (is_key_down(SDLK_LEFT))
        {
            player->rotation = fmod(player->rotation + 0.2, 6.28);
        }
        if (is_key_down(SDLK_RIGHT))
        {
            player->rotation = fmod(player->rotation - 0.2, 6.28);
        }
        if (is_key_down(SDLK_UP))
        {
            player->x += 20 * cos(player->rotation);
            player->y += 20 * sin(player->rotation);
        }

        if (is_key_down(SDLK_DOWN))
        {
            player->x -= 20 * cos(player->rotation);
            player->y -= 20 * sin(player->rotation);
        }
        SDL_Delay(5);
    }
}