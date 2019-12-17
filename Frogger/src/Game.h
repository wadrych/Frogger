#pragma once

#include <stdio.h>
#include <string.h>

#include "UserInterface.h"
#include "TextureManager.h"

#include "SDL.h"
#include "SDL_image.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handle_evnets();
	void update();
	void render();
	void clean();

	bool running();

private:
	bool is_running;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* scrtex;
	SDL_Surface* screen;
	SDL_Surface* charset;
	SDL_Surface* eti = NULL;

	int screen_width;
	int screen_height;

	Uint32 last_frame_time;
	Uint32 current_frame_time;

	int frames;

	double world_time;
	double fps_timer;
	double delta;
	double fps;
	double eti_speed;
	double distance;

	char text[128];
	int black;
	int green;
	int red;
	int blue;

	UserInterface* gui;

	void fps_counter();
	void calculate_time();

};
