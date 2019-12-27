#include "Car.h"

Car::Car(game_object* rect) : GameObject(rect)
{
	velocity = rect->v;
	street = 2 * SCREEN_WIDTH;
}

Car::~Car()
{
}

void Car::update()
{
	double distance = get_x() + velocity;
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

void Car::set_velocity(double v)
{
	velocity = v;
}

double Car::get_velocity()
{
	return velocity;
}



