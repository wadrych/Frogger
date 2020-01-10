#pragma once
#include "GameObject.h"
#include "stdlib.h"

class BonusFrog :
	public GameObject
{
public:
	BonusFrog(game_object* rect);
	~BonusFrog();

	void update(double delta_ms);
	bool is_visible();
	void set_visible(const bool v);
	void render();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	
private:
	bool is_on_sth_;
	bool visible_;
	long long int delta_;
	int occurance_interval_;
	bool to_display_;
};

