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

bool CollisonDetector::check_collisions_car(Player* p, Car* cars[], int cars_amt)
{
	for (int i = 0; i < cars_amt; i++)
	{
		if (CollisonDetector::check_collision(p->get_dest_rect(), cars[i]->get_dest_rect()))
		{
			return true;
		}
	}
	return false;
}

bool CollisonDetector::check_collision_border(Player* p)
{
	SDL_Rect left_river;
	SDL_Rect right_river;
	SDL_Rect grass;

	int amt_of_grass_rect = 4;

	left_river.x = -1;
	left_river.y = 0;
	left_river.w = 1;
	left_river.h = 192; //Height of water

	right_river.x = SCREEN_WIDTH;
	right_river.y = 0;
	right_river.w = 1;
	right_river.h = 192; //Height of water

	grass.x = 52;//position of first grass rect
	grass.y = 0;
	grass.w = 50;//dimensions of texture
	grass.h = 32;//dimensions of texture

	if(check_collision(p->get_dest_rect(), left_river) || check_collision(p->get_dest_rect(), right_river))
	{
		return true;
	}

	for(int i = 0; i < amt_of_grass_rect; i++)
	{
		if(check_collision(p->get_dest_rect(), grass))
		{
			return true;
		}

		grass.x += grass.w * 2; // skip water element and grass width
	}

	return false;
	
}

bool CollisonDetector::check_collisions_logs(Player* p, Log* logs[], int logs_amt)
{
	SDL_Rect temp;
	for (int i = 0; i < logs_amt; i++)
	{
		temp = logs[i]->get_dest_rect();
		temp.w = temp.w - (SCREEN_WIDTH / X_CHUNKS); 
		if (CollisonDetector::check_collision(p->get_dest_rect(), temp))
		{
			p->set_x(p->get_x() + logs[i]->get_velocity());
			return true;
		}
	}
	return false;
}

