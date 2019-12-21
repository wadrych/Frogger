#pragma once

#include "Global.h"
#include "TextureManager.h"

class Map
{
public:
	Map();
	~Map();

	void init(int width, int height);
	void render();
	
	SDL_Texture* get_texture();
	SDL_Rect get_dest_rect();
	SDL_Rect get_right_border();
	
private:
	SDL_Texture* texture;
	SDL_Rect src_r;
	SDL_Rect dest_r;
};

