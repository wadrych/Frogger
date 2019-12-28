#pragma once

#include "Player.h"
#include "Map.h"
#include "CollisionDetector.h"

class EventHandler
{
public:
	static void move_right(Player* p, Map* m);
	static void move_left(Player* p, Map* m);
	static void move_down(Player* p, Map* m);
	static void move_up(Player* p, Map* m);
};