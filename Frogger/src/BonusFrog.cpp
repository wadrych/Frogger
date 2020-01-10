#include "BonusFrog.h"

BonusFrog::BonusFrog(game_object* rect) : GameObject(rect)
{
	is_on_sth_ = true;
	visible_ = false;
	occurance_interval_ = rand() % 10;
	to_display_ = false;
}

BonusFrog::~BonusFrog()
{
}

void BonusFrog::update(double delta_ms)
{
	delta_ += delta_ms;

	if(!visible_)
	{
		if(delta_ >= occurance_interval_*1000)
		{
			to_display_ = true;
			delta_ = 0;
		}
	}

	if(to_display_ && pos_x_ > SCREEN_WIDTH)
	{
		visible_ = !visible_;
		to_display_ = false;
	}
	

	
	GameObject::update();
}

bool BonusFrog::is_visible()
{
	return visible_;
}

void BonusFrog::set_visible(const bool v)
{
	visible_ = v;
}

void BonusFrog::render()
{
	if(visible_)
	{
		GameObject::render();
	}
}

void BonusFrog::move_down()
{
	const int distance = 32;
	pos_y_ += distance;
}

void BonusFrog::move_up()
{
	const int distance = -32;
	pos_y_ += distance;
}

void BonusFrog::move_left()
{
	const int distance = -32;
	pos_x_ += distance;
}

void BonusFrog::move_right()
{
	const int distance = 32;
	pos_x_ += distance;
}

