#pragma once

#include "Player.h"
#include "Map.h"
#include "Car.h"
#include "CollisonDetector.h"

class EventHandler
{
public:
	static void move_right(Player* p, Map* m);
	static void move_left(Player* p, Map* m);
	static void move_down(Player* p, Map* m);
	static void move_up(Player* p, Map* m);
	static bool check_collisions(Player* p, Car* car_1[]);
};