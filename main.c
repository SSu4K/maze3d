#include "game.h"
#include "renderer.h"

#define MAP_SIZE 41
#define PLAYER_HEIGHT 20.0
#define PLAYER_RADIUS 15
#define PLAYER_FOV 1.5
#define BLOCK_WIDTH 50.0
#define BLOCK_HEIGHT 1000.0
#define LIGHT_INTENSITY 1000
#define RENDER_DISTANCE 300

int main(void)
{
    game_t game;
    game.level = new_rand_level(MAP_SIZE * BLOCK_WIDTH, MAP_SIZE * BLOCK_WIDTH, BLOCK_WIDTH, BLOCK_HEIGHT, 0.3);
    game.player = new_player(MAP_SIZE * BLOCK_WIDTH / 2, MAP_SIZE * BLOCK_WIDTH / 2, PLAYER_HEIGHT, PLAYER_RADIUS, 0, PLAYER_FOV, LIGHT_INTENSITY);
    game.render_distance = RENDER_DISTANCE;
    run_game(&game);

    free_game(&game);

    return 0;
}