#pragma once

#include "EntitiyManager.h"
#include "Map.h"
#include "CollisionDetector.h"
#include "UserInterface.h"

class EventHandler
{
public:
	static void move_right(Map* m);
	static void move_left(Map* m);
	static void move_down(Map* m);
	static void move_up(Map* m);
	static void quit_game(bool* is_running);
	static void restart_game(option* current, int spots[], EntitiyManager* entity_manager, double* world_time, int* score);
	static void pause_game(option* current);
	static void quit_menu(option* current);
	static void menu_up(option* current);
	static void menu_down(option* current);
	static void menu_launch(option* current, bool* is_running);
};