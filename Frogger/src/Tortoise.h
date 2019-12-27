#pragma once
#include "GameObject.h"
#include "stdlib.h""

class Tortoise :
	public GameObject
{
public:
	Tortoise(game_object* rect);
	~Tortoise();

	void update();
	void set_velocity(double v);
	double get_velocity();
	bool is_visible();
	void set_visible(bool v);
	void render();

private:
	double velocity;
	int street;
	bool visible;
	bool diving;
	int delta;
};

