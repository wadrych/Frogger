#include "CollisonDetector.h"


bool CollisonDetector::check_collision(SDL_Rect a, SDL_Rect b)
{
	int left_a, left_b;
	int right_a, right_b;
	int top_a, top_b;
	int bottom_a, bottom_b;

	left_a = a.x;
	right_a = a.x + a.w;
	top_a = a.y;
	bottom_a = a.y + a.h;
	
	left_b = b.x;
	right_b = b.x + b.w;
	top_b = b.y;
	bottom_b = b.y + b.h;

	if(bottom_a <= top_b)
	{
		return false;
	}

	if (top_a >= bottom_b)
	{
		return false;
	}

	if( right_a <= left_b)
	{
		return false;
	}

	if( left_a >= right_b)
	{
		return false;
	}

	return true;
}


