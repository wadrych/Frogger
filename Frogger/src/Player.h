#pragma once

#include "Global.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(game_object* rect);
	~Player();

	void move_up();
	void move_down();
	void move_left();
	void move_right();

private:
	int health;
};

