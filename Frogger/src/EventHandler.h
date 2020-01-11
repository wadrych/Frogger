#pragma once

#include "EntityManager.h"
#include "Map.h"
#include "CollisionDetector.h"
#include "UserInterface.h"

class EventHandler
{
public:
	static void handle_text_input(char name[8], SDL_bool* done);
	static void arrow_up(option* current, Map* map);
	static void arrow_down(option* current, Map* map);
	static void arrow_right(option current, Map* map);
	static void arrow_left(option current, Map* map);
	static void key_y(option* current, bool* is_running);
	static void key_n(option* current, bool* is_running, UserInterface* gui, Uint32* last_frame_time);
	static void key_p(option* current, Uint32* last_frame_time, UserInterface* gui);
	static void key_q(option* current, Uint32* last_frame_time, UserInterface* gui);
	static void key_enter(option* current, UserInterface* gui, bool* is_running);
private:
	static void menu_launch(option* current, bool* is_running);
	static void move_right(Map* m);
	static void move_left(Map* m);
	static void move_down(Map* m);
	static void move_up(Map* m);
	static void quit_game(bool* is_running);
	static void pause_game(option* current);
	static void quit_menu(option* current);
	static void menu_up(option* current);
	static void menu_down(option* current);
};