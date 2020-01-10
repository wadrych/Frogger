#pragma once
#include <stdio.h>
#include <cstring>

#include "Global.h"
#include "TextureManager.h"

enum option
{
	NEW_GAME,
	HIGH_SCORES,
	QUIT_GAME,
	GAME,
	GAME_OVER,
	PAUSE,
	MENU,
	QUIT,
	HIGH_SCORES_TABLE
};

class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void init(const int surface_height, const int surface_width, const int window_height);
	void update_info(double world_time, double fps, int player_health, int score);
	void update_menu(option current);
	void update_main_menu(option current);
	void render();
	void show_text(const char* text);
	void clean_menu();
	void destroy();
	void show_save_score(int score, char* name);
	void show_high_scores(result leaderboard[10], const int records_amt);
	void show_bonus(SDL_Rect rect, int bonus);
	
	SDL_Surface* create_time_bar(double world_time);
	
private:
	void draw_text_(SDL_Texture** texture, const char* text, bool wrap = false);
	void draw_rect_(SDL_Texture** texture, SDL_Rect tex_r, bool current);
	
	SDL_Texture* container_;
	SDL_Texture* menu_text_;
	SDL_Texture* bar_text_;
	SDL_Texture* menu_container_;
	SDL_Texture* main_menu_container_;
	SDL_Texture* game_name_;
	SDL_Texture* new_game_;
	SDL_Texture* new_game_text_;
	SDL_Texture* high_scores_;
	SDL_Texture* high_scores_text_;
	SDL_Texture* quit_;
	SDL_Texture* quit_text_;
	SDL_Texture* bonus_;
	SDL_Texture* high_scores_places_[10];
	
	SDL_Rect dest_r_;
	SDL_Rect dest_r_bar_;
	SDL_Rect dest_r_text_;
	SDL_Rect dest_r_menu_;
	SDL_Rect menu_r_;
	SDL_Rect game_name_r_;
	SDL_Rect new_game_r_;
	SDL_Rect new_game_t_r_;
	SDL_Rect high_scores_r_;
	SDL_Rect high_scores_t_r_;
	SDL_Rect quit_r_;
	SDL_Rect quit_t_r_;
	SDL_Rect bonus_r_;
	SDL_Rect high_score_places_r_[10];

	
	
	int surface_height_;
	int surface_width_;
};
