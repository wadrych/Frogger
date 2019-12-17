#pragma once

#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"

#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* load_texture(const char* file_name);
	static void draw_pixel(SDL_Surface* surface, int x, int y, Uint32 color);
	static void draw_line(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	static void draw_rectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
	static void draw_string(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
	static void draw_surface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
};
