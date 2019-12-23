#pragma once
#include "Global.h"
#include "GameObject.h"

class Log : public GameObject
{ 
public:
	Log(game_object *rect);
	~Log();

	void update();
	void set_velocity(int v);
	int get_velocity();
	
private:
	int velocity;
	int street;
};

