#pragma once
#include <stdio.h>
#include "TextureManager.h"

class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	bool init(int surface_height, int surface_width, int window_hight);
	SDL_Texture* update_info(double world_time, int fps);
	SDL_Rect get_destination_rect();
	
private:
	SDL_Texture* container;
	SDL_Surface* charset;
	SDL_Rect src_r;
	SDL_Rect dest_r;
	
	int surface_height;
	int surface_width;
};
