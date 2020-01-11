#pragma once
#include "GameObject.h"
#include "stdlib.h"

class Tortoise :
	public GameObject
{
public:
	Tortoise(game_object* rect);
	~Tortoise();

	void update(double delta_ms, double time);
	bool is_visible();
	void set_visible(const bool v);
	void render();

private:
	bool visible_;
	bool diving_;
	long long int delta_;
};

