#pragma once
#include "SDL.h"

#include "Player.h"
#include "Car.h"
#include "Log.h"
#include "Tortoise.h"

class CollisonDetector
{
public:
	static bool check_collision(SDL_Rect A, SDL_Rect B);
	static bool check_collisions_car(Player* p, Car* cars[], int cars_amt);
	static bool check_collision_border(Player* p);
	static bool check_collisions_water(Player* p, Log* logs[], int logs_amt, Tortoise* tortoises[], int tortoises_amt);
	static int check_collisions_spots(Player* p);
};

