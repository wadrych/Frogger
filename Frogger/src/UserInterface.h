#pragma once
#include <stdio.h>
#include "TextureManager.h"

class UserInterface
{
public:
	UserInterface(SDL_Surface* screen, int screen_height, int screen_width, SDL_Surface* charset);
	~UserInterface();

	void info_text(double world_time, int fps);

	SDL_Surface* screen;
	SDL_Surface* charset;
	int screen_height;
	int screen_width;
};
