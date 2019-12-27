#pragma once
#include "Global.h"
#include "GameObject.h"

class Log : public GameObject
{ 
public:
	Log(game_object *rect);
	~Log();

	void update();
	void set_velocity(double v);
	double get_velocity();
	
private:
	double velocity;
	int street;
};

