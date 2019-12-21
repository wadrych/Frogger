#pragma once
#include "SDL.h"

class CollisonDetector
{
public:
	static bool check_collision(SDL_Rect A, SDL_Rect B);
};

