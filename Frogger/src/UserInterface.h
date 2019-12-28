#pragma once
#include <stdio.h>
#include <cstring>

#include "Global.h"
#include "TextureManager.h"


class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void init(const int surface_height, const int surface_width, const int window_height);
	void update_info(double world_time, double fps, int player_health);
	void update_menu();
	
	void render();
	
	SDL_Texture* get_texture();
	SDL_Texture* get_texture_text();
	SDL_Texture* get_menu_texture();
	
private:
	SDL_Texture* container_;
	SDL_Texture* text_container_;
	SDL_Texture* menu_container_;
	SDL_Rect src_r_;
	SDL_Rect dest_r_;
	SDL_Rect src_r_text_;
	SDL_Rect dest_r_text_;
	SDL_Rect src_r_menu_;
	SDL_Rect dest_r_menu_;
	
	
	int surface_height_;
	int surface_width_;
};
