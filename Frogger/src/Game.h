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
	Game();
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

	Uint32 last_frame_time;
	Uint32 current_frame_time;

	int frames;

	double world_time;
	double fps_timer;
	double delta;
	double fps;

	game_object* player_s;
	game_object* cars_s;

	int cars_amt;

	void fps_counter();
	void calculate_time();
	void set_renderer_conf();
	void create_gui();
	void create_map();
	void load_structs();
	void free_structs();
	void create_player();
	void create_cars();
};
