#include "Tortoise.h"

Tortoise::Tortoise(game_object* rect) :GameObject(rect)
{
	velocity = rect->v;
	street = 2 * SCREEN_WIDTH;
	visible = true;
	if(rand()%4 == 0)
	{
		diving = true;
	}
	else
	{
		diving = false;
	}
}

Tortoise::~Tortoise()
{
}

void Tortoise::update()
{
	double distance = get_x() + velocity;
	if (distance > street)
	{
		distance = -SCREEN_WIDTH / X_CHUNKS * 6; // 6- cause log is max 6 tiles
	}

	if (distance < -SCREEN_WIDTH / X_CHUNKS * 6)// 6- cause log is max 6 tiles
	{
		distance = street;
	}

	if(diving)
	{
		delta += Global::time;
		if(delta >= 1000)
		{
			visible = !visible;
			delta = 0;
		}
	}

	set_x(distance);
	GameObject::update();
}

double Tortoise::get_velocity()
{
	return velocity;
}

void Tortoise::set_velocity(double v)
{
	velocity = v;
}

bool Tortoise::is_visible()
{
	return visible;
}

void Tortoise::set_visible(bool v)
{
	visible = v;
}

void Tortoise::render()
{
	if(visible)
	{
		GameObject::render();
	}
	else
	{
	}
	
}
