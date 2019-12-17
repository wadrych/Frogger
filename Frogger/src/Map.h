#pragma once

#include "SDL.h"
#include "TextureManager.h"

class Map
{
public:
	Map();
	~Map();

	void init(int width, int height);
	SDL_Texture* get_texture();
	SDL_Rect get_destination_rect();
private:
	SDL_Texture* texture;
	SDL_Rect src_r;
	SDL_Rect dest_r;
};

