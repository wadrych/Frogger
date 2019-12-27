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
	double distance = get_x() + velocity; // 0.05 to make things slower  
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

double Log::get_velocity()
{
	return  velocity;
}

void Log::set_velocity(double v)
{
	velocity = v;
}




