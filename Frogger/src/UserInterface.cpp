#include "UserInterface.h"
#include <cstring>

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

bool UserInterface::init(int surface_height, int surface_width, int window_hight)
{
	this->surface_height = surface_height;
	this->surface_width = surface_width;
	charset = NULL;
	
	charset = SDL_LoadBMP("assets/cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		dest_r.w = surface_width;
		dest_r.h = surface_height;
		dest_r.x = 0;
		dest_r.y = window_hight - surface_height;
		
		return true;
	}
	
}


SDL_Texture*  UserInterface::update_info(double world_time, int fps)
{
	SDL_Surface* temp_surface = SDL_CreateRGBSurface(0, surface_width, surface_height, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	
	char text[128];
	const Uint32 line_color = SDL_MapRGB(temp_surface->format, 0xFF, 0x00, 0x00);
	const Uint32 container_color = SDL_MapRGB(temp_surface->format, 0x00, 0x00, 0x00);

	TextureManager::draw_rectangle(temp_surface, 0,  0, surface_width, surface_height, line_color, container_color);
	sprintf(text, "Czas trwania = %.1lf s  %.0ld klatek / s", world_time, fps);
	TextureManager::draw_string(temp_surface, temp_surface->w / 2 - strlen(text) * 8 / 2, surface_height - 20, text, charset);

	container = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	return container;
	
}

SDL_Rect UserInterface::get_destination_rect()
{
	return dest_r;
}
