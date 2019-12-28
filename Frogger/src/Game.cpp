#include "Game.h"

SDL_Renderer* Global::renderer = NULL;
TTF_Font* Global::font = NULL;
long long int Global::time_delta = 0;

UserInterface* gui;
Map* map;
Player* player;
Car** cars;
Log** logs;
Tortoise** tortoises;

Game::Game()
{
	frames = 0;
	fps_timer = 0;
	fps = 0;
	world_time = 0;
	cars_amt = 0;
	spots[0] = 0;
	spots[1] = 0;
	spots[2] = 0;
	spots[3] = 0;
	spots[4] = 0;
	spots_amt = 5;
}

Game::~Game()
{
}

void Game::init(const char* title, const int x_pos, const int y_pos, const bool fullscreen)
{
	srand(time(NULL));
	
	is_running = sdl_initialization(title, x_pos, y_pos, fullscreen);

	set_renderer_conf();
	SDL_ShowCursor(SDL_DISABLE);
	
	last_frame_time = SDL_GetTicks();//Init of world time

	create_map();
	create_gui();

	load_entities();

	create_entities();
}

void Game::update()
{
	calculate_time();

	update_entities();
	
	check_collisions();
	
	player->update(); //if position of player was changed due to detected collisions apply the changes
	
	fps_counter();
	
	gui->update_info(world_time, fps);
	
	frames++;
}

void Game::render()
{
	SDL_RenderClear(Global::renderer);

	map->render();
	gui->render();

	render_spots();
	render_entities();

	SDL_RenderPresent(Global::renderer);
}

void Game::clean()
{
	SDL_DestroyTexture(screen);
	screen = NULL;

	SDL_DestroyTexture(gui->get_texture());
	
	SDL_DestroyTexture(gui->get_texture_text());

	SDL_DestroyTexture(map->get_texture());

	SDL_DestroyRenderer(Global::renderer);
	Global::renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	
	delete gui;
	delete map;

	
	destroy_entities();
	

	SDL_Quit();

	printf("Game cleaned\n");
}

void Game::handle_events()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) is_running = false;
		else if (event.key.keysym.sym == SDLK_UP) EventHandler::move_up(player, map);
		else if (event.key.keysym.sym == SDLK_DOWN) EventHandler::move_down(player, map);
		else if (event.key.keysym.sym == SDLK_LEFT) EventHandler::move_left(player, map);
		else if (event.key.keysym.sym == SDLK_RIGHT) EventHandler::move_right(player, map);
		break;

	case SDL_KEYUP:
		break;

	case SDL_QUIT:
		is_running = false;
		break;

	default:
		break;
	};

}

bool Game::running()
{
	return is_running;
}

void Game::fps_counter()
{
	fps_timer += delta;
	if (fps_timer > 0.5) {
		fps = frames * 2;

		frames = 0;
		fps_timer -= 0.5;
	};
}

void Game::calculate_time()
{
	const double to_seconds = 0.001;

	current_frame_time = SDL_GetTicks();

	Global::time_delta = (current_frame_time - last_frame_time);
	delta = Global::time_delta * to_seconds;
	last_frame_time = current_frame_time;

	world_time += delta;
}

void Game::create_gui()
{
	gui = new UserInterface;
	gui->init(GUI_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::create_map()
{
	int map_height = SCREEN_HEIGHT - GUI_HEIGHT;
	map = new Map;
	map->init(SCREEN_WIDTH, map_height);
}

void Game::set_renderer_conf()
{
	SDL_SetRenderDrawColor(Global::renderer, 0, 0, 255, 255);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(Global::renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::create_cars()
{
	cars = (Car**)malloc(cars_amt * sizeof(Car*));
	
	for (int i = 0; i < cars_amt; i++)
	{
		cars[i] = new Car(&cars_s[i]);
	}
}

void Game::load_entities()
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

	logs_amt = 13;
	logs_s = (game_object*)malloc(logs_amt * sizeof(game_object));
	logs_s[0] = { SCREEN_WIDTH * 0, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[1] = { SCREEN_WIDTH * 1 / 2, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[2] = { SCREEN_WIDTH * 1 / 1, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[3] = { SCREEN_WIDTH * 3 / 2, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[4] = { SCREEN_WIDTH * (-1) / 2, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s[5] = { SCREEN_WIDTH * 0, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1 };
	logs_s[6] = { SCREEN_WIDTH * 8 / 14, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1 };
	logs_s[7] = { SCREEN_WIDTH * 16 / 14, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1 };
	logs_s[8] = { SCREEN_WIDTH * 24 / 14, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1 };
	logs_s[9] = { SCREEN_WIDTH * 0, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 0.5 };
	logs_s[10] = { SCREEN_WIDTH * 3 / 4, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 0.5 };
	logs_s[11] = { SCREEN_WIDTH * 5 / 4, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 0.5 };
	logs_s[12] = { SCREEN_WIDTH * 7 / 4, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 0.5 };

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
}

void Game::create_player()
{
	player = new Player(player_s);
}
void Game::create_logs()
{
	logs = (Log**)malloc(logs_amt * sizeof(Log*));
	
	for (int i = 0; i < logs_amt; i++)
	{
		logs[i] = new Log(&logs_s[i]);
	}
}

void Game::create_tortoises()
{
	tortoises = (Tortoise**)malloc(tortoises_amt * sizeof(Tortoise*));

	for (int i = 0; i < tortoises_amt; i++)
	{
		tortoises[i] = new Tortoise(&tortoises_s[i]);
	}
}

void Game::fail()
{
	player->set_x(player_s->x);
	player->set_y(player_s->y);
}

void Game::success()
{
	player->set_x(player_s->x);
	player->set_y(player_s->y);

	if(check_if_won())
	{
		printf("You won!");
	}
}


bool Game::check_if_won()
{
	for(int i=0; i < spots_amt; i++)
	{
		if (spots[i] == 0)
		{
			return false;
		}
	}
	return true;
}

void Game::check_collisions()
{
	const int spot = CollisonDetector::check_collisions_spots(player);
	if (spot != -1)
	{
		if (spots[spot] == 1)
		{
			fail();
		}
		else
		{
			spots[spot] = 1;
			success();
		}
	}

	CollisonDetector::check_collisions_water(player, logs, logs_amt, tortoises, tortoises_amt);
	if (CollisonDetector::check_collisions_car(player, cars, cars_amt))
	{
		fail();
	}

	if (CollisonDetector::check_collision_border(player))
	{
		fail();
	}
}

void Game::update_entities()
{
	player->update();
	
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
		tortoises[i]->update();
	}
}

bool Game::sdl_initialization(const char* title, const int x_pos, const int y_pos, const bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		printf("SDL initialized!\n");
		window = SDL_CreateWindow(title, x_pos, y_pos, SCREEN_WIDTH, SCREEN_HEIGHT, flags);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			printf("Window initialized!\n");
			Global::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (Global::renderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				printf("Renderer initialized!\n");

				const int img_flags = IMG_INIT_PNG;

				if (!(IMG_Init(img_flags) & img_flags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					return false;
				}
				else
				{
					printf("SDL_image initialized!\n");
					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						return false;
					}
					else
					{
						printf("SDL_ttf initialized!\n");
						Global::font = TTF_OpenFont("../../TTF/UniversCondensed.ttf", 28);
						if (Global::font == NULL)
						{
							printf("Font could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
							return false;
						}
						else
						{
							printf("Font initialized!\n");
							return true;
						}
					}
				}
			}
		}
	}						
}

void Game::render_entities()
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
}

void Game::render_spots()
{
	for (int i = 0; i < spots_amt; i++)
	{
		if (spots[i] == 1)
		{
			SDL_Rect temp;
			temp.x = 16 + i * 96;
			temp.y = 16;
			temp.w = 32;
			temp.h = 32;
			SDL_RenderCopy(Global::renderer, player->get_texture(), &(player->get_src_rect()), &temp);
		}
	}
}

void Game::destroy_entities()
{
	SDL_DestroyTexture(player->get_texture());
	
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
}

void Game::create_entities()
{
	player = new Player(player_s);
	create_cars();
	create_logs();
	create_tortoises();
}
