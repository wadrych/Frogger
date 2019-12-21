#pragma once

#include <stdio.h>
#include <string.h>
#include <cmath>

#include "Global.h"
#include "UserInterface.h"
#include "Map.h"
#include "Player.h"
#include "Car.h"
#include "EventHandler.h"

class Game
{
public:
	Game(int width, int height, int gui_h);
	~Game();

	void init(const char* title, int xpos, int ypos, bool fullscreen);

	void handle_evnets();
	void update();
	void render();
	void clean();

	bool running();

private:
	bool is_running;
	SDL_Window* window;
	SDL_Texture* screen;
	SDL_Surface* charset;

	const int screen_width;
	const int screen_height;
	const int gui_height;

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
