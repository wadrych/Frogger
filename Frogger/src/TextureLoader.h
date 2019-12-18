#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "Game.h"

class TextureLoader
{
public:
	static SDL_Texture* load_texture(const char* file_name);
};

