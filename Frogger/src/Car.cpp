#include "Car.h"

Car::Car(game_object* rect) : GameObject(rect)
{
	velocity = rect->v;
	street = 2 * SCREEN_WIDTH;
}

Car::~Car()
{
}

void Car::update(double time)
{
	int distance = get_x() + velocity;
	if( distance > street)
	{
		distance = -SCREEN_WIDTH / X_CHUNKS;
	}

	if(distance < -SCREEN_WIDTH / X_CHUNKS)
	{
		distance = street;
	}

	set_x(distance);
	GameObject::update();
}

void Car::set_velocity(int v)
{
	velocity = v;
}

int Car::get_velocity()
{
	return velocity;
}



