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

SDL_Rect Map::get_destination_rect()
{
	return dest_r;
}


