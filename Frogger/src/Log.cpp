#include "Log.h"

Log::Log(game_object* rect) : GameObject(rect)
{
	velocity = rect->v;
	street = 2 * SCREEN_WIDTH;
}

Log::~Log()
{
}

void Log::update()
{
	int distance = get_x() + velocity;
	if (distance > street)
	{
		distance = -SCREEN_WIDTH / X_CHUNKS * 6; // 6- cause log is max 6 tiles
	}

	if (distance < -SCREEN_WIDTH / X_CHUNKS * 6)// 6- cause log is max 6 tiles
	{
		distance = street;
	}

	set_x(distance);
	GameObject::update();
}

int Log::get_velocity()
{
	return  velocity;
}

void Log::set_velocity(int v)
{
	velocity = v;
}




