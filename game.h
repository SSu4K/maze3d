#ifndef __GAME_H__
#define __GAME_H__

#include <math.h>
#include "level.h"

typedef struct Player
{
    double camera_height;
    double player_radius;
    double x;
    double y;
    double rotation;
    double fov;
    double light_intenstity;
} player_t;

typedef struct Game
{
    level_t *level;
    player_t *player;
} game_t;

player_t *new_player(double x, double y, double height, double radius, double rotation, double fov, double intensity);
void free_game(game_t *game);
void run_game(game_t *game);

#endif