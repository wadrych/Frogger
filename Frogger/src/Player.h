#pragma once

#include "Global.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(const char* path, int x, int y);
	~Player();

	void move_x(int distance);
	void move_y(int distance);

private:
	int health;
};

