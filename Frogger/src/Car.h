#pragma once
#include "Global.h"
#include "GameObject.h"

class Car : public GameObject
{
public:
	Car(game_object* rect);
	~Car();
	
	void update();
	void set_velocity(double v);
	double get_velocity();
	
private:
	double velocity;
	int street;
};

