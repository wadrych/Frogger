#include "UserInterface.h"

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::init(const int surface_height, const int surface_width, const int window_height)
{
	this->surface_height_ = surface_height;
	this->surface_width_ = surface_width;
	
	dest_r_.w = surface_width;
	dest_r_.h = surface_height;
	dest_r_.x = 0;
	dest_r_.y = window_height - surface_height;
	dest_r_text_.w = surface_width / 2;
	dest_r_text_.h = surface_height - 2;
	dest_r_text_.x = 0;
	dest_r_text_.y = dest_r_.y;

}


void  UserInterface::update_info(double world_time, double fps)
{
	SDL_DestroyTexture(container_);
	SDL_DestroyTexture(text_container_);
	
	SDL_Surface* temp_surface = SDL_CreateRGBSurface(0, surface_width_, surface_height_, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if(temp_surface == NULL)
	{
		printf("Unable to create RGB surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		char text[128];
		const Uint32 line_color = SDL_MapRGB(temp_surface->format, 0xFF, 0x00, 0x00);
		const Uint32 container_color = SDL_MapRGB(temp_surface->format, 0x00, 0x00, 0x00);

		TextureManager::draw_rectangle(temp_surface, 0, 0, surface_width_, surface_height_, line_color, container_color);

		sprintf(text, "Czas trwania = %.1lf s  %.0lf klatek / s", world_time, fps);
		SDL_Surface* text_surface = TTF_RenderText_Solid(Global::font, text, { 255,255,255 });

		if (text_surface == NULL)
		{
			printf("Unable to create TTF surface ! TTF Error: %s\n", TTF_GetError());
		}
		else
		{
			container_ = SDL_CreateTextureFromSurface(Global::renderer, temp_surface);
			text_container_ = SDL_CreateTextureFromSurface(Global::renderer, text_surface);
			if(container_  == NULL || text_container_ == NULL)
			{
				printf("Unable to create gui textures ! SDL Error: %s\n", SDL_GetError());
			}
			SDL_FreeSurface(text_surface);
		}
		SDL_FreeSurface(temp_surface);
	}
}

SDL_Texture* UserInterface::get_texture()
{
	return container_;
}

void UserInterface::render()
{
	SDL_RenderCopy(Global::renderer, container_, NULL, &dest_r_);
	SDL_RenderCopy(Global::renderer, text_container_, NULL, &dest_r_text_);
}

SDL_Texture* UserInterface::get_texture_text()
{
	return text_container_;
}
