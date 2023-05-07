#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "renderer.h"

static SDL_Renderer *renderer = NULL;
static SDL_Window *window = NULL;

// Screen dimension constants
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int window_width()
{
	return WINDOW_WIDTH;
}

int window_height()
{
	return WINDOW_HEIGHT;
}

void window_update()
{
	rectangleRGBA(renderer, 0, 0, WINDOW_WIDTH-1, WINDOW_HEIGHT-1, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

int is_key_down(int key)
{
	const Uint8 *keytable;
	int numkeys;
	SDL_PumpEvents();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(3);
		}
	}
	keytable = SDL_GetKeyboardState(&numkeys);
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	assert(code < numkeys);
	return keytable[code];
}

static void renderer_close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int renderer_init()
{

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(renderer_close);

	window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
							  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		fprintf(stderr, "Window could not be created! SDL Error: %s\n",
				SDL_GetError());
		return 2;
	}
	else
	{
		// Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer == NULL)
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
		}

		if (renderer == NULL)
		{
			fprintf(stderr, "Renderer could not be created! SDL Error: %s\n",
					SDL_GetError());
			return 3;
		}
	}

	SDL_Delay(10);
	return 0;
}

void draw_lineRGB(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	lineRGBA(renderer, x1, y1, x2, y2, r, g, b,
			 255);
}

void vertical_line(int x, int y1, int y2, SDL_Color color){
	vlineRGBA(renderer, x, y1, y2, color.r, color.g, color.b, 255);
}

void vertical_lineRGB(int x, int y1, int y2, int r, int g, int b){
	vlineRGBA(renderer, x, y1, y2, r, g, b, 255);
}

void vertical_shaded_line(int x, int y1, int y2, SDL_Color color, double sq_distance_1, double sq_distance_2, double sq_real_length, double intensity){
	double A=sq_real_length;
	double B=3*sq_distance_1+sq_distance_2-sq_real_length;
	double C=sq_distance_1;
	double t=0;
	double dt=1/(y2-y1);
	double brightness=1;
	for(int y=0;y<y2-y1;y++){
		brightness=intensity/(A*t*t+B*t+C);
		if(brightness>1) brightness=1;
		SDL_SetRenderDrawColor(renderer, color.r*brightness, color.g*brightness, color.b*brightness, 255);
		SDL_RenderDrawPoint(renderer, x, y1+y);
		t+=dt;
	}
}