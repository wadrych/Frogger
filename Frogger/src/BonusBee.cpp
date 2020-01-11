#include "BonusBee.h"

BonusBee::BonusBee(game_object* rect) : GameObject(rect)
{
	visible_ = false;
	occurrence_interval_ = rand() % 4 + 6;
	spots_[0] = 0;
	spots_[1] = 0;
	spots_[2] = 0;
	spots_[3] = 0;
	spots_[4] = 0;
}


BonusBee::~BonusBee()
{
}

void BonusBee::update(double delta_ms)
{
	delta_ += delta_ms;

	if(!visible_)
	{
		if(delta_ >= occurrence_interval_*1000)
		{
			do
			{
				spot_number_ = rand() % 5;
			} while (spots_[spot_number_] != 0);

			const int width_from_left_border = 16;
			const int width_of_spot_and_grass = 64 + 32;

			pos_x_ = width_from_left_border + (width_of_spot_and_grass)*spot_number_;

			visible_ = true;
			delta_ = 0;
			
		}
	}


	GameObject::update();
}

bool BonusBee::is_visible()
{
	return visible_;
}

void BonusBee::set_visible(const bool v)
{
	visible_ = v;
}

void BonusBee::render()
{
	if(visible_)
	{
		GameObject::render();
	}
}

void BonusBee::reset()
{
	visible_ = false;
	delta_ = 0;
}

void BonusBee::take_spot(const int spot)
{
	spots_[spot] = 1;
}

void BonusBee::clean()
{
	reset();
	spots_[0] = 0;
	spots_[1] = 0;
	spots_[2] = 0;
	spots_[3] = 0;
	spots_[4] = 0;
	
}
