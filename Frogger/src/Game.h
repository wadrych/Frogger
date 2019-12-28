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
	bool is_running_;
	SDL_Window* window_;
	SDL_Texture* screen_;

	Uint32 last_frame_time_;
	Uint32 current_frame_time_;

	int frames_;

	double world_time_;
	double fps_timer_;
	double delta_;
	double fps_;

	game_object* player_s_;
	game_object* cars_s_;
	game_object* logs_s_;
	game_object* tortoises_s_;

	int cars_amt_;
	int logs_amt_;
	int tortoises_amt_;
	int spots_[5];
	int spots_amt_;


	bool sdl_initialization(const char* title, const int x_pos, const int y_pos, const bool fullscreen);
	void fps_counter();
	void calculate_time();
	void set_renderer_conf();
	void create_gui();
	void create_map();
	void fail();
	void success();
	bool check_if_won();
	void check_collisions();
	void render_spots();

	void load_entities();
	void create_entities();
	void update_entities();
	void render_entities();
	void destroy_entities();

	void create_player();
	void create_cars();
	void create_logs();
	void create_tortoises();
	
};
