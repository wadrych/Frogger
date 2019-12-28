#pragma once
#include "SDL.h"

#include "Player.h"
#include "Tortoise.h"

class CollisionDetector
{
public:
	static bool check_collision(SDL_Rect A, SDL_Rect B);
	static bool check_collisions_car(Player* p, GameObject* cars[], int cars_amt);
	static bool check_collision_border(Player* p);
	static bool check_collisions_water(Player* p, GameObject* logs[], int logs_amt, Tortoise* tortoises[], int tortoises_amt);
	static int check_collisions_spots(Player* p);
};

