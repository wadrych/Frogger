#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

class Global
{
public:
	static SDL_Renderer* renderer;
	static TTF_Font* font;
};