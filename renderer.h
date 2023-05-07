#ifndef __RENDERER_H__
#define __RENDERE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int window_width();
int window_height();
int renderer_init();
void window_update();
int is_key_down(int key);
void draw_lineRGB(int x1, int y1, int x2, int y2, int r, int g, int b);
void vertical_line(int x, int y1, int y2, SDL_Color color);
void vertical_lineRGB(int x, int y1, int y2, int r, int g, int b);
void vertical_shaded_line(int x, int y1, int y2, SDL_Color color, double sq_distance_1, double sq_distance_2, double sq_real_length, double intensity);

#endif