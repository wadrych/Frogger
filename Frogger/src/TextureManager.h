#pragma once

#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"

#include "Game.h"
#include "TextureLoader.h"

class TextureManager
{
public:
	void draw_pixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void draw_line(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	void draw_rectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
	void draw_string(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
	void draw_surface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
	SDL_Texture* get_texture();
private:
	
	SDL_Texture* tex;
};
