#pragma once

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stdlib.h"
#include <time.h>

#include "Global.h"
#include "UserInterface.h"
#include "Map.h"
#include "EventHandler.h"
#include "EntitiyManager.h"

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
	bool game_over_;
	bool paused_;
	bool quit_;
	SDL_Window* window_;
	SDL_Texture* screen_;

	Uint32 last_frame_time_;
	Uint32 current_frame_time_;

	EntitiyManager* entitiy_manager_;

	int frames_;

	double world_time_;
	double fps_timer_;
	double delta_;
	double fps_;

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
	void check_time();
};
