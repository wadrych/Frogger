#include "UserInterface.h"
#include <cstring>

UserInterface::UserInterface(SDL_Surface* screen, int screen_height, int screen_width, SDL_Surface* charset)
{
	this->screen = screen;
	this->screen_height = screen_height;
	this->screen_width = screen_width;
	this->charset = charset;
}

UserInterface::~UserInterface()
{
}


void UserInterface::info_text(double world_time, int fps)
{
	char text[128];
	const int line_color = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	const int container_color = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	TextureManager::draw_rectangle(screen, 4, screen_height - 30, screen_width - 8, 26, line_color, container_color);
	sprintf(text, "Czas trwania = %.1lf s  %.0ld klatek / s", world_time, fps);
	TextureManager::draw_string(screen, screen->w / 2 - strlen(text) * 8 / 2, screen_height - 20, text, charset);

}