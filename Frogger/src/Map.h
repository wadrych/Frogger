#pragma once

#include "Global.h"
#include "TextureManager.h"

class Map
{
public:
	Map();
	~Map();

	void init(const int width, const int height);
	void render();
	
	SDL_Texture* get_texture();
	SDL_Rect get_dest_rect();
	
private:
	SDL_Texture* texture_;
	SDL_Rect src_r_;
	SDL_Rect dest_r_;
};

