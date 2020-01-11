#pragma once

#include "Global.h"
#include "GameObject.h"
#include "Player.h"
#include "Tortoise.h"
#include "BonusFrog.h"
#include "BonusBee.h"

class EntityManager
{
public:

	EntityManager();
	~EntityManager();

	void init();
	void update(double delta_ms);
	void render();
	void destroy();

	static Player* player;
	static GameObject** cars;
	static GameObject** logs;
	static Tortoise** tortoises;
	static BonusFrog* bonus_frog;
	static BonusBee* bonus_bee;
	
	static int cars_amt;
	static int logs_amt;
	static int tortoises_amt;

	game_object* player_s;
	game_object* cars_s;
	game_object* logs_s;
	game_object* tortoises_s;
	game_object* bonus_frog_s;
	game_object* bonus_bee_s;
	
private:
	void create_cars();
	void create_logs();
	void create_tortoises();
	void create_player();
	void load();
	void create();
	void create_bonus_frog();
	void create_bonus_bee();
};

