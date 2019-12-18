#include "Map.h"

Map::Map()
{
}

Map::~Map()
{	
}

bool Map::init(int dest_width, int dest_height)
{
	dest_r.w = dest_width;
	dest_r.h = dest_height;
	dest_r.x = 0;
	dest_r.y = 0;

	texture = TextureManager::load_texture("assets/map.png");

	if(texture == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

SDL_Texture* Map::get_texture()
{
	return texture;
}

void Map::render()
{
	SDL_RenderCopy(Game::renderer, texture, NULL, &dest_r);
}


