#pragma once

#include "Global.h"
#include "GameObject.h"
#include  "Player.h"
#include  "Tortoise.h"
#include "BonusFrog.h"

class EntitiyManager
{
public:

	EntitiyManager();
	~EntitiyManager();

	void init();
	void update();
	void render();
	void destroy();

	static Player* player;
	static GameObject** cars;
	static GameObject** logs;
	static Tortoise** tortoises;
	static BonusFrog* bonus_frog;
	
	static int cars_amt;
	static int logs_amt;
	static int tortoises_amt;

	static game_object* player_s;
	static game_object* cars_s;
	static game_object* logs_s;
	static game_object* tortoises_s;
	static game_object* bonus_frog_s;
	
private:
	void create_cars();
	void create_logs();
	void create_tortoises();
	void create_player();
	void load();
	void create();
	void create_bonus_frog();

	
	
};

