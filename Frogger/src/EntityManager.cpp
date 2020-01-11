#include "EntityManager.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::init()
{
	load();
	create();
}


void EntityManager::load()
{
	player_s = (game_object*)malloc(sizeof(game_object));
	*player_s = { 32 * 7 , 32 * 12 + 16, 32, 32,  "assets/frogger.png", 0 };

	cars_amt = 14;
	cars_s = (game_object*)malloc(cars_amt * sizeof(game_object));
	cars_s[0] = { SCREEN_WIDTH * 0, 11 * 32 + 16, 32, 32, "assets/car_1.png", -1.5 };
	cars_s[1] = { SCREEN_WIDTH / 2, 11 * 32 + 16, 32, 32, "assets/car_1.png", -1.5 };
	cars_s[2] = { SCREEN_WIDTH * 1, 11 * 32 + 16, 32, 32, "assets/car_1.png", -1.5 };
	cars_s[3] = { SCREEN_WIDTH * 3 / 2, 11 * 32 + 16, 32, 32, "assets/car_1.png", -1.5 };
	cars_s[5] = { SCREEN_WIDTH * 0, 10 * 32 + 16, 32, 32, "assets/car_4.png", 0.5 };
	cars_s[6] = { SCREEN_WIDTH * 2 / 3, 10 * 32 + 16, 32, 32, "assets/car_4.png", 0.5 };
	cars_s[7] = { SCREEN_WIDTH * 2 * 2 / 3, 10 * 32 + 16, 32, 32, "assets/car_4.png", 0.5 };
	cars_s[8] = { SCREEN_WIDTH / 2, 9 * 32 + 16, 32, 32, "assets/car_2.png", -1 };
	cars_s[9] = { SCREEN_WIDTH * 1, 9 * 32 + 16, 32, 32, "assets/car_2.png", -1 };
	cars_s[10] = { SCREEN_WIDTH * 3 / 2, 9 * 32 + 16, 32, 32, "assets/car_2.png", -1 };
	cars_s[11] = { SCREEN_WIDTH * 0, 9 * 32 + 16, 32, 32, "assets/car_2.png", -1 };
	cars_s[12] = { SCREEN_WIDTH * 1, 8 * 32 + 16, 32, 32, "assets/car_3.png", 8 };
	cars_s[13] = { SCREEN_WIDTH * 0, 7 * 32 + 16, 64, 32, "assets/car_5.png", -0.5 };
	cars_s[4] = { SCREEN_WIDTH * 1, 7 * 32 + 16, 64, 32, "assets/car_5.png", -0.5 };

	logs_amt = 17;
	logs_s = (game_object*)malloc(logs_amt * sizeof(game_object));
	logs_s[0] = { SCREEN_WIDTH * 0, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[1] = { SCREEN_WIDTH * 4 / 14, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[2] = { SCREEN_WIDTH * 8 / 14, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[3] = { SCREEN_WIDTH * 12 / 14, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[4] = { SCREEN_WIDTH * 16 / 14, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[13] = { SCREEN_WIDTH * 20 / 14, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[14] = { SCREEN_WIDTH * 24 / 14, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[15] = { SCREEN_WIDTH * 28 / 14, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[16] = { SCREEN_WIDTH * -3 / 14, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };


	logs_s[5] = { SCREEN_WIDTH * 0, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1.5 };
	logs_s[6] = { SCREEN_WIDTH * 8 / 14, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1.5 };
	logs_s[7] = { SCREEN_WIDTH * 16 / 14, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1.5 };
	logs_s[8] = { SCREEN_WIDTH * 24 / 14, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1.5 };

	logs_s[9] = { SCREEN_WIDTH * 0, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 1 };
	logs_s[10] = { SCREEN_WIDTH * 3 / 4, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 1 };
	logs_s[11] = { SCREEN_WIDTH * 5 / 4, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 1 };
	logs_s[12] = { SCREEN_WIDTH * 7 / 4, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 1 };

	tortoises_amt = 16;
	tortoises_s = (game_object*)malloc(tortoises_amt * sizeof(game_object));
	tortoises_s[0] = { SCREEN_WIDTH * 0, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s[1] = { SCREEN_WIDTH * 4 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s[2] = { SCREEN_WIDTH * 8 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s[3] = { SCREEN_WIDTH * 12 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s[4] = { SCREEN_WIDTH * 16 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s[5] = { SCREEN_WIDTH * 20 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s[6] = { SCREEN_WIDTH * 24 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s[7] = { SCREEN_WIDTH * 28 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s[8] = { SCREEN_WIDTH * 0 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s[9] = { SCREEN_WIDTH * 3 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s[10] = { SCREEN_WIDTH * 6 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s[11] = { SCREEN_WIDTH * 9 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s[12] = { SCREEN_WIDTH * 16 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s[13] = { SCREEN_WIDTH * 19 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s[14] = { SCREEN_WIDTH * 22 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s[15] = { SCREEN_WIDTH * 25 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };

	bonus_frog_s = (game_object*)malloc(sizeof(game_object));
	bonus_frog_s[0].x = logs_s[14].x;
	bonus_frog_s[0].y = logs_s[14].y;
	bonus_frog_s[0].v = logs_s[14].v;
	bonus_frog_s[0].h = logs_s[14].h;
	bonus_frog_s[0].w = 32;
	bonus_frog_s[0].path = "assets/frog_bonus.png";

	bonus_bee_s = (game_object*)malloc(sizeof(game_object));
	bonus_bee_s[0] = { 16 , 0 + 16, 32, 32,  "assets/frog_bonus.png", 0 };
}

void EntityManager::create()
{
	create_player();
	create_cars();
	create_logs();
	create_tortoises();
	create_bonus_frog();
	create_bonus_bee();
}

void EntityManager::create_cars()
{
	cars = (GameObject**)malloc(cars_amt * sizeof(GameObject*));

	for (int i = 0; i < cars_amt; i++)
	{
		cars[i] = new GameObject(&cars_s[i]);
	}
}

void EntityManager::create_logs()
{
	logs = (GameObject**)malloc(logs_amt * sizeof(GameObject*));

	for (int i = 0; i < logs_amt; i++)
	{
		logs[i] = new GameObject(&logs_s[i]);
	}
}

void EntityManager::create_tortoises()
{
	tortoises = (Tortoise**)malloc(tortoises_amt * sizeof(Tortoise*));

	for (int i = 0; i < tortoises_amt; i++)
	{
		tortoises[i] = new Tortoise(&tortoises_s[i]);
	}
}

void EntityManager::update(double delta_ms)
{
	player->update();

	bonus_frog->update(delta_ms);

	bonus_bee->update(delta_ms);

	for (int i = 0; i < cars_amt; i++)
	{
		cars[i]->update();
	}

	for (int i = 0; i < logs_amt; i++)
	{
		logs[i]->update();
	}

	for (int i = 0; i < tortoises_amt; i++)
	{
		tortoises[i]->update(delta_ms);
	}
}

void EntityManager::render()
{
	for (int i = 0; i < cars_amt; i++)
	{
		cars[i]->render();
	}
	for (int i = 0; i < logs_amt; i++)
	{
		logs[i]->render();
	}
	for (int i = 0; i < tortoises_amt; i++)
	{
		tortoises[i]->render();
	}

	player->render();
	bonus_frog->render();
	bonus_bee->render();
}

void EntityManager::destroy()
{
	SDL_DestroyTexture(player->get_texture());
	SDL_DestroyTexture(bonus_frog->get_texture());
	SDL_DestroyTexture(bonus_bee->get_texture());
	for (int i = 0; i < cars_amt; i++)
	{
		SDL_DestroyTexture(cars[i]->get_texture());
	}
	for (int i = 0; i < logs_amt; i++)
	{
		SDL_DestroyTexture(logs[i]->get_texture());
	}
	for (int i = 0; i < tortoises_amt; i++)
	{
		SDL_DestroyTexture(tortoises[i]->get_texture());
	}

	delete player;
	delete bonus_frog;
	delete bonus_bee;
	for (int i = 0; i < cars_amt; i++)
	{
		delete cars[i];
	}
	for (int i = 0; i < logs_amt; i++)
	{
		delete logs[i];
	}
	for (int i = 0; i < tortoises_amt; i++)
	{
		delete tortoises[i];
	}

	free(player_s);
	free(cars_s);
	free(logs_s);
	free(tortoises_s);
	free(bonus_frog_s);
	free(bonus_bee_s);
}

void EntityManager::create_player()
{
	player = new Player(player_s);
	player->init();
}

void EntityManager::create_bonus_frog()
{
	bonus_frog = new BonusFrog(bonus_frog_s);
}

void EntityManager::create_bonus_bee()
{
	bonus_bee = new BonusBee(bonus_bee_s);
}
