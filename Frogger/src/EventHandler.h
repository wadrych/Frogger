#pragma once

#include "EntitiyManager.h"
#include "Map.h"
#include "CollisionDetector.h"

class EventHandler
{
public:
	static void move_right(Map* m);
	static void move_left(Map* m);
	static void move_down(Map* m);
	static void move_up(Map* m);
	static void quit_game(bool* is_running);
	static void restart_game(bool* game_over);
};