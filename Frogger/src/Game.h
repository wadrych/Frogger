#pragma once

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stdlib.h"
#include <time.h>

#include "Global.h"
#include "UserInterface.h"
#include "Map.h"
#include "Player.h"
#include "Car.h"
#include "Log.h"
#include "Tortoise.h"
#include "EventHandler.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int x_pos, int y_pos, bool fullscreen);

	void handle_events();
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
	game_object* logs_s;
	game_object* tortoises_s;

	int cars_amt;
	int logs_amt;
	int tortoises_amt;
	int spots[5];
	int spots_amt;

	void fps_counter();
	void calculate_time();
	void set_renderer_conf();
	void create_gui();
	void create_map();
	void load_entities();
	void create_player();
	void create_cars();
	void create_logs();
	void create_tortoises();
	void fail();
	void success();
	bool check_if_won();
	void check_collisions();
	void update_entities();
	bool sdl_initialization(const char* title, const int x_pos, const int y_pos, const bool fullscreen);
	void render_spots();
	void render_entities();
	void destroy_entities();
	void create_entities();
	
};
