#include "Map.h"

Map::Map()
{
}

Map::~Map()
{	
}

void Map::init(const int width, const int height)
{
	dest_r_.w = width;
	dest_r_.h = height;
	dest_r_.x = 0;
	dest_r_.y = 0;

	texture_ = TextureManager::load_texture("assets/map.png");
}

SDL_Texture* Map::get_texture()
{
	return texture_;
}

void Map::render()
{
	SDL_RenderCopy(Global::renderer, texture_, NULL, &dest_r_);
}

SDL_Rect Map::get_dest_rect()
{
	return dest_r_;
}


