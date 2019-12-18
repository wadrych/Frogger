#include "TextureManager.h"

SDL_Texture* TextureManager::load_texture(const char* file_name)
{
	
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

void TextureManager::draw_string(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;

	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	}
}

void TextureManager::draw_surface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

SDL_Texture* TextureManager::get_texture()
{
	return tex;
}
