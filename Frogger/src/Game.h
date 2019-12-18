#pragma once

#include <stdio.h>
#include <string.h>

#include "UserInterface.h"
#include "TextureManager.h"
#include "Map.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <string>
#include <cmath>


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


	static SDL_Renderer* renderer;
	static TTF_Font* font;

private:
	bool is_running;
	SDL_Window* window;
	SDL_Texture* screen;
	SDL_Surface* charset;

	int screen_width;
	int screen_height;

	Uint32 last_frame_time;
	Uint32 current_frame_time;

	int frames;

	double world_time;
	double fps_timer;
	double delta;
	double fps;
	double distance;

	char text[128];
	int black;
	int green;
	int red;
	int blue;

	void fps_counter();
	void calculate_time();
	void create_gui(int gui_height);
	void create_map(int map_height);
	void set_renderer_conf();

};
