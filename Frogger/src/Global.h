#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#define SCREEN_WIDTH 448
#define	SCREEN_HEIGHT 458
#define GUI_HEIGHT 26
#define X_CHUNKS 14
#define Y_CHUNKS 13

class Global
{
public:
	static SDL_Renderer* renderer;
	static TTF_Font* font;
	static int time;
};