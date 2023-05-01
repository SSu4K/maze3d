#include "game.h"

#define MAP_SIZE 21
#define PLAYER_HEIGHT 20.0
#define PLAYER_RADIUS 15
#define PLAYER_FOV 2.0
#define BLOCK_WIDTH 50.0
#define BLOCK_HEIGHT 1000.0

int main(void)
{
    game_t game;
    game.level = new_rand_level(MAP_SIZE, MAP_SIZE, BLOCK_WIDTH, BLOCK_HEIGHT, 0.3);
    game.player = new_player(MAP_SIZE*BLOCK_WIDTH/2, MAP_SIZE*BLOCK_WIDTH/2, PLAYER_HEIGHT, PLAYER_RADIUS, 0, PLAYER_FOV);
    
    run_game(&game);

    free_game(&game);

    return 0;
}