#pragma once
#include <stdio.h>
#include <cstring>

#include "Global.h"
#include "TextureManager.h"

enum menu_mode
{
	GAME_OVER,
	PAUSE,
	MENU,
	QUIT
};

class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void init(const int surface_height, const int surface_width, const int window_height);
	void update_info(double world_time, double fps, int player_health, int score);
	void update_menu(menu_mode mode);
	void render();
	void show_text(const char* text);
	void clean_menu();
	
	SDL_Surface* create_time_bar(double world_time);
	
	SDL_Texture* get_texture();
	SDL_Texture* get_texture_text();
	SDL_Texture* get_menu_texture();
	SDL_Texture* get_menu_text_texture();
	
	
private:
	SDL_Texture* container_;
	SDL_Texture* menu_text_;
	SDL_Texture* bar_text_;
	SDL_Texture* menu_container_;
	SDL_Rect src_r_;
	SDL_Rect dest_r_;
	SDL_Rect src_r_bar_;
	SDL_Rect dest_r_bar_;
	SDL_Rect src_r_text_;
	SDL_Rect dest_r_text_;
	SDL_Rect src_r_menu_;
	SDL_Rect dest_r_menu_;
	
	
	int surface_height_;
	int surface_width_;
};
