#include "TextureManager.h"

SDL_Texture* TextureManager::load_texture(const char* file_name)
{
	SDL_Texture* tex;
	SDL_Surface* temp_surface = IMG_Load(file_name);

	tex = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	return tex;
}


void TextureManager::draw_pixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
}

void TextureManager::draw_line(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color)
{
	for (int i = 0; i < l; i++) {
		draw_pixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}

void TextureManager::draw_rectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor)
{
	int i;
	draw_line(screen, x, y, k, 0, 1, outlineColor);
	draw_line(screen, x + l - 1, y, k, 0, 1, outlineColor);
	draw_line(screen, x, y, l, 1, 0, outlineColor);
	draw_line(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		draw_line(screen, x + 1, i, l - 2, 1, 0, fillColor);
}