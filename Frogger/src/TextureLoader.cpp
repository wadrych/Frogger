#include "TextureLoader.h"

SDL_Texture* TextureLoader::load_texture(const char* file_name)
{
	SDL_Texture* tex;
	SDL_Surface* temp_surface = IMG_Load(file_name);
	
	tex = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	return tex;
}
