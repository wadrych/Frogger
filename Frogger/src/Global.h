#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#define SCREEN_WIDTH 448
#define	SCREEN_HEIGHT 458
#define GUI_HEIGHT 26
#define X_CHUNKS 14
#define Y_CHUNKS 13

typedef struct game_object
{
	int x, y;
	int w, h;
	const char* path;
	double v;
} game_object;

typedef  struct result {
	int score;
	char* name;
} result;

class Global
{
public:
	static SDL_Renderer* renderer;
	static TTF_Font* font;
	static long long int time_delta;
};