#pragma once
#include "Global.h"
#include "GameObject.h"

class Car : public GameObject
{
public:
	Car(const char* path, int x, int y, int v, int screen_width);
	~Car();
	
	void update(double time);
	void set_velocity(int v);
	int get_velocity();
private:
	int velocity;
	int street;
	
};

