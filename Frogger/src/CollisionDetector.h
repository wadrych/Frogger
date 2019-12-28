#pragma once
#include "SDL.h"

#include "EntitiyManager.h"

class CollisionDetector
{
public:
	static bool check_collision(SDL_Rect A, SDL_Rect B);
	static bool check_collisions_car();
	static bool check_collision_border();
	static bool check_collisions_water();
	static int check_collisions_spots();
};

