#pragma once

#include <stdio.h>

#include "Global.h"

class TextureManager
{
public:
	
	/**
	 * \brief Loads texture from specified location
	 * \param file_name 
	 * \return Texture on success or NULL
	 */
	static SDL_Texture* load_texture(const char* file_name);
	
	/**
	 * \brief Draws pixel
	 * \param surface 
	 * \param x 
	 * \param y 
	 * \param color 
	 */
	static void draw_pixel(SDL_Surface* surface, int x, int y, Uint32 color);
	
	/**
	 * \brief Draws line
	 * \param screen 
	 * \param x 
	 * \param y 
	 * \param l 
	 * \param dx 
	 * \param dy 
	 * \param color 
	 */
	static void draw_line(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	
	/**
	 * \brief Draws rectangle
	 * \param screen 
	 * \param x 
	 * \param y 
	 * \param l 
	 * \param k 
	 * \param outlineColor 
	 * \param fillColor 
	 */
	static void draw_rectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
};
