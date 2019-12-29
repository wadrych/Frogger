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
	dest_r_.h = surface_height - 2;
	dest_r_.x = 0;
	dest_r_.y = window_height - surface_height;

	dest_r_bar_.w = surface_width / 4;
	dest_r_bar_.h = surface_height - 2;
	dest_r_bar_.x = 0;
	dest_r_bar_.y = window_height - surface_height;

	dest_r_menu_.w = surface_width - 40;
	dest_r_menu_.h = window_height - 100;
	dest_r_menu_.x = 20;
	dest_r_menu_.y = 50;
}


void  UserInterface::update_info(double world_time, double fps, int player_health, int score)
{	
	SDL_DestroyTexture(bar_text_);
	SDL_DestroyTexture(container_);
	
	char text[128];
	
	sprintf(text, "Health %2i Score %4i", player_health,score);
	SDL_Surface* text_surface = TTF_RenderText_Solid(Global::font, text, { 255,255,255 });

	SDL_Surface* temp = create_time_bar(world_time);
	
	if (text_surface == NULL)
	{
		printf("Unable to create TTF surface ! TTF Error: %s\n", TTF_GetError());
	}
	else
	{
		container_ = SDL_CreateTextureFromSurface(Global::renderer, temp);
		bar_text_ = SDL_CreateTextureFromSurface(Global::renderer, text_surface);
		if(bar_text_ == NULL)
		{
			printf("Unable to create gui textures ! SDL Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(text_surface);
	}
	SDL_FreeSurface(temp);

}

SDL_Surface* UserInterface::create_time_bar(double world_time)
{
	const int health_bar_pixels = 200;
	const int game_time = 50;

	dest_r_.w = (int)(health_bar_pixels * (1 - (world_time / game_time)));

	//prevention against rect with 0 width
	if (dest_r_.w == 0)
	{
		dest_r_.w = 1;
	}

	dest_r_.x = SCREEN_WIDTH - dest_r_.w;

	SDL_Surface* temp = SDL_CreateRGBSurface(0, dest_r_.w, dest_r_.h, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	Uint32 outline = SDL_MapRGB(temp->format, 0x00, 0x00, 0x00);
	Uint32 fill = SDL_MapRGB(temp->format, 0xFF, 0xFF, 0x00);

	if (world_time >= 40 && world_time < 50)
	{
		fill = SDL_MapRGB(temp->format, 0xFF, 0x00, 0x00);
	}

	TextureManager::draw_rectangle(temp, 0, 0, dest_r_.w, dest_r_.h, outline, fill);

	return temp;
}


SDL_Texture* UserInterface::get_texture()
{
	return container_;
}

void UserInterface::render()
{

	SDL_RenderCopy(Global::renderer, container_, NULL, &dest_r_);
	SDL_RenderCopy(Global::renderer, bar_text_, NULL, &dest_r_bar_);
	SDL_RenderCopy(Global::renderer, menu_container_, NULL, &dest_r_menu_);
	SDL_RenderCopy(Global::renderer, menu_text_, NULL, &dest_r_text_);
}

SDL_Texture* UserInterface::get_texture_text()
{
	return menu_text_;
}



void UserInterface::update_menu(menu_mode mode)
{
	if (mode == GAME_OVER)
	{
		dest_r_text_.w = dest_r_menu_.w - 200;
		dest_r_text_.h = 25;
		dest_r_text_.x = dest_r_menu_.x + 100;
		dest_r_text_.y = dest_r_menu_.y + 160;
		show_text("GAME OVER QUIT? Y/N");
	}
	else if (mode == PAUSE)
	{
		dest_r_text_.w = dest_r_menu_.w - 300;
		dest_r_text_.h = 25;
		dest_r_text_.x = dest_r_menu_.x + 150;
		dest_r_text_.y = dest_r_menu_.y + 160;
		show_text("PAUSE");
	}
	else if (mode == QUIT)
	{
		dest_r_text_.w = dest_r_menu_.w - 300;
		dest_r_text_.h = 25;
		dest_r_text_.x = dest_r_menu_.x + 150;
		dest_r_text_.y = dest_r_menu_.y + 160;
		show_text("QUIT GAME? Y/N");
	}
	
}

SDL_Texture* UserInterface::get_menu_texture()
{
	return menu_container_;
}

void UserInterface::clean_menu()
{
	SDL_DestroyTexture(menu_container_);
	SDL_DestroyTexture(menu_text_);
}

void UserInterface::show_text(const char* text)
{
	clean_menu();
	
	SDL_Surface* temp_surface = SDL_CreateRGBSurface(0, dest_r_menu_.w, dest_r_menu_.h, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (temp_surface == NULL)
	{
		printf("Unable to create RGB surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		char text_buffer[128];
		const Uint32 line_color = SDL_MapRGB(temp_surface->format, 0xFF, 0x00, 0x00);
		const Uint32 container_color = SDL_MapRGB(temp_surface->format, 0x00, 0x00, 0x00);

		TextureManager::draw_rectangle(temp_surface, 0, 0, dest_r_menu_.w, dest_r_menu_.h, line_color, container_color);

		sprintf(text_buffer, text);
		SDL_Surface* text_surface = TTF_RenderText_Solid(Global::font, text, { 255,255,255 });

		if (text_surface == NULL)
		{
			printf("Unable to create TTF surface ! TTF Error: %s\n", TTF_GetError());
		}
		else
		{
			menu_container_ = SDL_CreateTextureFromSurface(Global::renderer, temp_surface);
			menu_text_ = SDL_CreateTextureFromSurface(Global::renderer, text_surface);
			if (menu_container_ == NULL || menu_text_ == NULL)
			{
				printf("Unable to create menu texture ! SDL Error: %s\n", SDL_GetError());
			}
			SDL_FreeSurface(text_surface);
		}
		SDL_FreeSurface(temp_surface);
	}
}

SDL_Texture* UserInterface::get_menu_text_texture()
{
	return bar_text_;
}
