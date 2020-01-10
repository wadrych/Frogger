#include "Tortoise.h"

Tortoise::Tortoise(game_object* rect) :GameObject(rect)
{
	velocity_ = rect->v;
	street_ = 2 * SCREEN_WIDTH;
	visible_ = true;
	
	if(rand()%6 == 0)
	{
		diving_ = true;
	}
	else
	{
		diving_ = false;
	}
}

Tortoise::~Tortoise()
{
}

void Tortoise::update(double delta_ms)
{
	if(diving_)
	{
		delta_ += delta_ms;
		if(delta_ >= 1000)
		{
			visible_ = !visible_;
			delta_ = 0;
		}
	}
	
	GameObject::update();
}

bool Tortoise::is_visible()
{
	return visible_;
}

void Tortoise::set_visible(const bool v)
{
	visible_ = v;
}

void Tortoise::render()
{
	if(visible_)
	{
		GameObject::render();
	}
}
