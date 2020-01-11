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
#include "EntityManager.h"
#include "ScoreManager.h"

class Game
{
public:
	Game();
	~Game();
	
	void init(const char* title, int x_pos, int y_pos);

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

	EntityManager* entity_manager_;
	ScoreManager* score_manager_;
	UserInterface* gui_;
	Map* map_;

	int frames_;

	double world_time_;
	double fps_timer_;
	double delta_s_;
	double delta_ms_;
	double fps_;
	double game_time_;

	int spots_[5];
	int spots_amt_;

	int score_;
	int last_position_;
	int bonus_;
	option current_;


	bool sdl_initialization(const char* title, const int x_pos, const int y_pos);
	void fps_counter();
	void calculate_time();
	void set_renderer_conf();
	void create_gui();
	void create_map();
	void fail();
	void success(int spot);
	void handle_score();
	bool check_if_won();
	void handle_collisions();
	void render_spots();
	void check_time();
	void game_continue();
	void start();
	void calculate_bonus();
};
