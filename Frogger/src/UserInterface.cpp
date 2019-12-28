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

	dest_r_menu_.w = surface_width - 40;
	dest_r_menu_.h = window_height - 100;
	dest_r_menu_.x = 20;
	dest_r_menu_.y = 50;
}


void  UserInterface::update_info(double world_time, double fps, int player_health)
{
	dest_r_text_.w = surface_width_ / 2;
	dest_r_text_.h = surface_height_ - 2;
	dest_r_text_.x = 0;
	dest_r_text_.y = dest_r_.y;
	
	SDL_DestroyTexture(container_);
	SDL_DestroyTexture(text_container_);
	SDL_DestroyTexture(menu_container_);
	
	char text[128];
	
	sprintf(text, "Health %2i                   ", player_health);
	SDL_Surface* text_surface = TTF_RenderText_Solid(Global::font, text, { 255,255,255 });

	if (text_surface == NULL)
	{
		printf("Unable to create TTF surface ! TTF Error: %s\n", TTF_GetError());
	}
	else
	{
		text_container_ = SDL_CreateTextureFromSurface(Global::renderer, text_surface);
		if(text_container_ == NULL)
		{
			printf("Unable to create gui textures ! SDL Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(text_surface);
	}
}

SDL_Texture* UserInterface::get_texture()
{
	return container_;
}

void UserInterface::render()
{
	SDL_RenderCopy(Global::renderer, menu_container_, NULL, &dest_r_menu_);
	SDL_RenderCopy(Global::renderer, container_, NULL, &dest_r_);
	SDL_RenderCopy(Global::renderer, text_container_, NULL, &dest_r_text_);
}

SDL_Texture* UserInterface::get_texture_text()
{
	return text_container_;
}

void UserInterface::update_menu()
{
	SDL_DestroyTexture(menu_container_);
	SDL_DestroyTexture(text_container_);

	dest_r_text_.w = dest_r_menu_.w - 100;
	dest_r_text_.h = dest_r_menu_.h - 300;
	dest_r_text_.x = dest_r_menu_.x + 50;
	dest_r_text_.y = dest_r_menu_.y + 150;

	SDL_Surface* temp_surface = SDL_CreateRGBSurface(0, dest_r_menu_.w, dest_r_menu_.h, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (temp_surface == NULL)
	{
		printf("Unable to create RGB surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		char text[128];
		const Uint32 line_color = SDL_MapRGB(temp_surface->format, 0xFF, 0x00, 0x00);
		const Uint32 container_color = SDL_MapRGB(temp_surface->format, 0x00, 0x00, 0x00);

		TextureManager::draw_rectangle(temp_surface, 0, 0, dest_r_menu_.w, dest_r_menu_.h, line_color, container_color);
		
		sprintf(text, "GAME OVER Quit game? Y/N");
		SDL_Surface* text_surface = TTF_RenderText_Solid(Global::font, text, { 255,255,255 });

		if (text_surface == NULL)
		{
			printf("Unable to create TTF surface ! TTF Error: %s\n", TTF_GetError());
		}
		else
		{
			menu_container_ = SDL_CreateTextureFromSurface(Global::renderer, temp_surface);
			text_container_ = SDL_CreateTextureFromSurface(Global::renderer, text_surface);
			if (menu_container_ == NULL || text_container_ == NULL)
			{
				printf("Unable to create gui textures ! SDL Error: %s\n", SDL_GetError());
			}
			SDL_FreeSurface(text_surface);
		}
		SDL_FreeSurface(temp_surface);
	}
}

SDL_Texture* UserInterface::get_menu_texture()
{
	return menu_container_;
}
