#include "Map.h"

Map::Map()
{
}

Map::~Map()
{	
}

void Map::init(int dest_width, int dest_height)
{
	dest_r.w = dest_width;
	dest_r.h = dest_height;
	dest_r.x = 0;
	dest_r.y = 0;

	texture = TextureManager::load_texture("assets/map.png");
}

SDL_Texture* Map::get_texture()
{
	return texture;
}

void Map::render()
{
	SDL_RenderCopy(Global::renderer, texture, NULL, &dest_r);
}

SDL_Rect Map::get_dest_rect()
{
	return dest_r;
}

SDL_Rect Map::get_right_border()
{
	SDL_Rect r;

	r.h = dest_r.h;
	r.w = 1;
	r.x = dest_r.w;
	r.y = 0;

	return r;
}


