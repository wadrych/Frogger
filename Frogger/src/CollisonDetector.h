#pragma once
#include "SDL.h"

#include "Player.h"
#include "Car.h"

class CollisonDetector
{
public:
	static bool check_collision(SDL_Rect A, SDL_Rect B);
	static bool check_collisions_car(Player* p, Car* cars[], int cars_amt);
	static bool check_collision_border(Player* p);
};

