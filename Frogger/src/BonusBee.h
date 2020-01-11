#pragma once
#include "GameObject.h"
#include "stdlib.h"

class BonusBee : public GameObject
{
public:
	BonusBee(game_object* rect);
	~BonusBee();

	void update(double delta_ms);
	bool is_visible();
	void set_visible(const bool v);
	void render();
	void reset();
	void clean();
	void take_spot(const int spot);
private:
	bool visible_;
	long long int delta_;
	int occurrence_interval_;
	int spot_number_;
	int spots_[5];
};

