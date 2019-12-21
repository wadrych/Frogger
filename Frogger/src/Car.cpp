#include "Car.h"

Car::Car(const char* path, int x, int y, int v, int screen_width) : GameObject(path, x, y)
{
	set_velocity(v);
	street = screen_width;
}

Car::~Car()
{
}

void Car::update(double time)
{
	int distance = get_x() - velocity;
	if( distance < -street)
	{
		distance = street;
	}

	update_x(distance);
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



