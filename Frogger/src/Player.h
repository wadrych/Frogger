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
	bool is_above_water();
	void set_is_above_water(bool n);
	void lost();
	bool is_alive();
	int health();
	void init();
	void attach_frog();
	void lose_frog();
	bool has_frog();
	void reset_pos();

private:
	int health_;
	bool is_on_sth_;
	bool is_alive_;
	bool has_frog_;

	int start_x_;
	int start_y_;
};

