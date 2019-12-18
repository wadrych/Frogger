#pragma once
#include <stdio.h>
#include <cstring>

#include <SDL_ttf.h>
#include "TextureManager.h"
#include "Game.h"


class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void init(int surface_height, int surface_width, int window_hight);
	void update_info(double world_time, int fps);
	void render();
	SDL_Texture* get_texture();
	SDL_Texture* get_texture_text();
	
private:
	SDL_Texture* container;
	SDL_Texture* text_container;
	SDL_Surface* charset;
	SDL_Rect src_r;
	SDL_Rect dest_r;
	SDL_Rect src_r_text;
	SDL_Rect dest_r_text;
	
	int surface_height;
	int surface_width;
};
