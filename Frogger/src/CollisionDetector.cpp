#include "CollisionDetector.h"

int EntitiyManager::cars_amt;
int EntitiyManager::logs_amt;
int EntitiyManager::tortoises_amt;

bool CollisionDetector::check_collision(SDL_Rect a, SDL_Rect b)
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

bool CollisionDetector::check_collisions_car()
{
	for (int i = 0; i < EntitiyManager::cars_amt; i++)
	{
		if (CollisionDetector::check_collision(EntitiyManager::player->get_dest_rect(), EntitiyManager::cars[i]->get_dest_rect()))
		{
			return true;
		}
	}
	return false;
}

bool CollisionDetector::check_collision_border()
{
	SDL_Rect left_river;
	SDL_Rect right_river;
	SDL_Rect grass;
	SDL_Rect river;

	const int amt_of_grass_rect = 4;

	left_river.x = -1;
	left_river.y = 0;
	left_river.w = 1;
	left_river.h = 32* 6 + 16; //Height of water

	right_river.x = SCREEN_WIDTH;
	right_river.y = 0;
	right_river.w = 1;
	right_river.h = 32 * 6 + 16; //Height of water

	grass.x = 64;//position of first grass rect
	grass.y = 0;
	grass.w = 32;//dimensions of texture
	grass.h = 32 + 16;//dimensions of texture

	river.x = 0;
	river.y = 32 + 16;
	river.h = 5 * 32;
	river.w = SCREEN_WIDTH;

	if(check_collision(EntitiyManager::player->get_dest_rect(), left_river) || check_collision(EntitiyManager::player->get_dest_rect(), right_river))
	{
		return true;
	}

	for(int i = 0; i < amt_of_grass_rect; i++)
	{
		if(check_collision(EntitiyManager::player->get_dest_rect(), grass))
		{
			return true;
		}

		grass.x += grass.w + 64; // skip water element and grass width
	}

	if(check_collision(EntitiyManager::player->get_dest_rect(), river) && !EntitiyManager::player->is_above_water())
	{
		return true;
	}

	return false;
	
}

bool CollisionDetector::check_collisions_water()
{
	SDL_Rect temp;
	
	for (int i = 0; i < EntitiyManager::logs_amt; i++)
	{
		temp = EntitiyManager::logs[i]->get_dest_rect();
		temp.x = temp.x + (SCREEN_WIDTH / X_CHUNKS / 2); // so to make rect in the middle of log with 1/2 of 32x32 offset 
		temp.w = temp.w - (SCREEN_WIDTH / X_CHUNKS);  // from width delete one 32x32
		if (CollisionDetector::check_collision(EntitiyManager::player->get_dest_rect(), temp))
		{
			EntitiyManager::player->set_x(EntitiyManager::player->get_x() + EntitiyManager::logs[i]->get_velocity());
			EntitiyManager::player->set_is_above_water(true);

			return true;
		}
	}
	
	for (int i = 0; i < EntitiyManager::tortoises_amt; i++)
	{
		if (EntitiyManager::tortoises[i]->is_visible())
		{
			temp = EntitiyManager::tortoises[i]->get_dest_rect();
			temp.x = temp.x + (SCREEN_WIDTH / X_CHUNKS / 2); // so to make rect in the middle of log with 1/2 of 32x32 offset 
			temp.w = temp.w - (SCREEN_WIDTH / X_CHUNKS);  // from width delete one 32x32
			if (CollisionDetector::check_collision(EntitiyManager::player->get_dest_rect(), temp))
			{
				EntitiyManager::player->set_x(EntitiyManager::player->get_x() + EntitiyManager::tortoises[i]->get_velocity());
				EntitiyManager::player->set_is_above_water(true);

				return true;
			}
		}
	}
	
	EntitiyManager::player->set_is_above_water(false);
	return false;
}

int CollisionDetector::check_collisions_spots()
{
	SDL_Rect spot;

	const int amt_of_grass_spots = 5;
	
	spot.x = 0;//position of first spot rect
	spot.y = 0;
	spot.w = 64;//dimensions of texture
	spot.h = 32 + 16;//dimensions of texture

	
	for(int i = 0; i < amt_of_grass_spots; i++)
	{
		if(check_collision(EntitiyManager::player->get_dest_rect(), spot))
		{
			if(abs(EntitiyManager::player->get_dest_rect().x - spot.x) < 32)
			{
				return i;
			}
		}

		spot.x += spot.w + 32; // skip spot and grass width
	}

	return -1;
}

bool CollisionDetector::caught_bee()
{
	return check_collision(EntitiyManager::player->get_dest_rect(), EntitiyManager::bonus_bee->get_dest_rect());
}