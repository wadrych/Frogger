#pragma once

#include "SDL.h"
#include "TextureManager.h"

class Map
{
public:
	Map();
	~Map();

	bool init(int width, int height);
	void render();
	SDL_Texture* get_texture();
	
private:
	SDL_Texture* texture;
	SDL_Rect src_r;
	SDL_Rect dest_r;
};

