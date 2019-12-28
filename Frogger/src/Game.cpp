#include "Game.h"

SDL_Renderer* Global::renderer = NULL;
TTF_Font* Global::font = NULL;
long long int Global::time_delta = 0;

UserInterface* gui;
Map* map;
Player* player;
GameObject** cars;
GameObject** logs;
Tortoise** tortoises;

Game::Game()
{
	frames_ = 0;
	fps_timer_ = 0;
	fps_ = 0;
	world_time_ = 0;
	cars_amt_ = 0;
	spots_[0] = 0;
	spots_[1] = 0;
	spots_[2] = 0;
	spots_[3] = 0;
	spots_[4] = 0;
	spots_amt_ = 5;
}

Game::~Game()
{
}

void Game::init(const char* title, const int x_pos, const int y_pos, const bool fullscreen)
{
	srand(time(NULL));
	
	is_running_ = sdl_initialization(title, x_pos, y_pos, fullscreen);

	set_renderer_conf();
	SDL_ShowCursor(SDL_DISABLE);
	
	last_frame_time_ = SDL_GetTicks();//Init of world time

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
	
	gui->update_info(world_time_, fps_);
	
	frames_++;
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
	SDL_DestroyTexture(screen_);
	screen_ = NULL;

	SDL_DestroyTexture(gui->get_texture());
	
	SDL_DestroyTexture(gui->get_texture_text());

	SDL_DestroyTexture(map->get_texture());

	SDL_DestroyRenderer(Global::renderer);
	Global::renderer = NULL;

	SDL_DestroyWindow(window_);
	window_ = NULL;

	
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
		if (event.key.keysym.sym == SDLK_ESCAPE) is_running_ = false;
		else if (event.key.keysym.sym == SDLK_UP) EventHandler::move_up(player, map);
		else if (event.key.keysym.sym == SDLK_DOWN) EventHandler::move_down(player, map);
		else if (event.key.keysym.sym == SDLK_LEFT) EventHandler::move_left(player, map);
		else if (event.key.keysym.sym == SDLK_RIGHT) EventHandler::move_right(player, map);
		break;

	case SDL_KEYUP:
		break;

	case SDL_QUIT:
		is_running_ = false;
		break;

	default:
		break;
	};

}

bool Game::running()
{
	return is_running_;
}

void Game::fps_counter()
{
	fps_timer_ += delta_;
	if (fps_timer_ > 0.5) {
		fps_ = frames_ * 2;

		frames_ = 0;
		fps_timer_ -= 0.5;
	};
}

void Game::calculate_time()
{
	const double to_seconds = 0.001;

	current_frame_time_ = SDL_GetTicks();

	Global::time_delta = (current_frame_time_ - last_frame_time_);
	delta_ = Global::time_delta * to_seconds;
	last_frame_time_ = current_frame_time_;

	world_time_ += delta_;
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
	cars = (GameObject**)malloc(cars_amt_ * sizeof(GameObject*));
	
	for (int i = 0; i < cars_amt_; i++)
	{
		cars[i] = new GameObject(&cars_s_[i]);
	}
}

void Game::load_entities()
{
	player_s_ = (game_object*)malloc(sizeof(game_object));
	*player_s_ = { 32 * 7 , 32 * 12 + 16, 32, 32,  "assets/frogger.png", 0 };

	cars_amt_ = 14;
	cars_s_ = (game_object*)malloc(cars_amt_ * sizeof(game_object));
	cars_s_[0] = { SCREEN_WIDTH * 0, 11 * 32 + 16, 32, 32, "assets/car_1.png", -1.5 };
	cars_s_[1] = { SCREEN_WIDTH / 2, 11 * 32 + 16, 32, 32, "assets/car_1.png", -1.5 };
	cars_s_[2] = { SCREEN_WIDTH * 1, 11 * 32 + 16, 32, 32, "assets/car_1.png", -1.5 };
	cars_s_[3] = { SCREEN_WIDTH * 3 / 2, 11 * 32 + 16, 32, 32, "assets/car_1.png", -1.5 };
	cars_s_[5] = { SCREEN_WIDTH * 0, 10 * 32 + 16, 32, 32, "assets/car_4.png", 0.5 };
	cars_s_[6] = { SCREEN_WIDTH * 2 / 3, 10 * 32 + 16, 32, 32, "assets/car_4.png", 0.5 };
	cars_s_[7] = { SCREEN_WIDTH * 2 * 2 / 3, 10 * 32 + 16, 32, 32, "assets/car_4.png", 0.5 };
	cars_s_[8] = { SCREEN_WIDTH / 2, 9 * 32 + 16, 32, 32, "assets/car_2.png", -1 };
	cars_s_[9] = { SCREEN_WIDTH * 1, 9 * 32 + 16, 32, 32, "assets/car_2.png", -1 };
	cars_s_[10] = { SCREEN_WIDTH * 3 / 2, 9 * 32 + 16, 32, 32, "assets/car_2.png", -1 };
	cars_s_[11] = { SCREEN_WIDTH * 0, 9 * 32 + 16, 32, 32, "assets/car_2.png", -1 };
	cars_s_[12] = { SCREEN_WIDTH * 1, 8 * 32 + 16, 32, 32, "assets/car_3.png", 8 };
	cars_s_[13] = { SCREEN_WIDTH * 0, 7 * 32 + 16, 64, 32, "assets/car_5.png", -0.5 };
	cars_s_[4] = { SCREEN_WIDTH * 1, 7 * 32 + 16, 64, 32, "assets/car_5.png", -0.5 };

	logs_amt_ = 13;
	logs_s_ = (game_object*)malloc(logs_amt_ * sizeof(game_object));
	logs_s_[0] = { SCREEN_WIDTH * 0, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s_[1] = { SCREEN_WIDTH * 1 / 2, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s_[2] = { SCREEN_WIDTH * 1 / 1, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s_[3] = { SCREEN_WIDTH * 3 / 2, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s_[4] = { SCREEN_WIDTH * (-1) / 2, 32 * 4 + 16, 32 * 3,32,"assets/log_short.png", 0.5 };
	logs_s_[5] = { SCREEN_WIDTH * 0, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1 };
	logs_s_[6] = { SCREEN_WIDTH * 8 / 14, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1 };
	logs_s_[7] = { SCREEN_WIDTH * 16 / 14, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1 };
	logs_s_[8] = { SCREEN_WIDTH * 24 / 14, 32 * 3 + 16, 32 * 6,32,"assets/log_long.png", 1 };
	logs_s_[9] = { SCREEN_WIDTH * 0, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 0.5 };
	logs_s_[10] = { SCREEN_WIDTH * 3 / 4, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 0.5 };
	logs_s_[11] = { SCREEN_WIDTH * 5 / 4, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 0.5 };
	logs_s_[12] = { SCREEN_WIDTH * 7 / 4, 32 * 1 + 16, 32 * 5,32,"assets/log_mid.png", 0.5 };

	tortoises_amt_ = 16;
	tortoises_s_ = (game_object*)malloc(tortoises_amt_ * sizeof(game_object));
	tortoises_s_[0] = { SCREEN_WIDTH * 0, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s_[1] = { SCREEN_WIDTH * 4 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s_[2] = { SCREEN_WIDTH * 8 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s_[3] = { SCREEN_WIDTH * 12 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s_[4] = { SCREEN_WIDTH * 16 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s_[5] = { SCREEN_WIDTH * 20 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s_[6] = { SCREEN_WIDTH * 24 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s_[7] = { SCREEN_WIDTH * 28 / 14, 32 * 5 + 16, 32 * 3,32,"assets/tortoise_3.png", -1 };
	tortoises_s_[8] = { SCREEN_WIDTH * 0 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s_[9] = { SCREEN_WIDTH * 3 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s_[10] = { SCREEN_WIDTH * 6 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s_[11] = { SCREEN_WIDTH * 9 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s_[12] = { SCREEN_WIDTH * 16 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s_[13] = { SCREEN_WIDTH * 19 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s_[14] = { SCREEN_WIDTH * 22 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
	tortoises_s_[15] = { SCREEN_WIDTH * 25 / 14, 32 * 2 + 16, 32 * 2,32,"assets/tortoise_2.png", -1 };
}

void Game::create_player()
{
	player = new Player(player_s_);
}
void Game::create_logs()
{
	logs = (GameObject**)malloc(logs_amt_ * sizeof(GameObject*));
	
	for (int i = 0; i < logs_amt_; i++)
	{
		logs[i] = new GameObject(&logs_s_[i]);
	}
}

void Game::create_tortoises()
{
	tortoises = (Tortoise**)malloc(tortoises_amt_ * sizeof(Tortoise*));

	for (int i = 0; i < tortoises_amt_; i++)
	{
		tortoises[i] = new Tortoise(&tortoises_s_[i]);
	}
}

void Game::fail()
{
	player->set_x(player_s_->x);
	player->set_y(player_s_->y);
}

void Game::success()
{
	player->set_x(player_s_->x);
	player->set_y(player_s_->y);

	if(check_if_won())
	{
		printf("You won!");
	}
}


bool Game::check_if_won()
{
	for(int i=0; i < spots_amt_; i++)
	{
		if (spots_[i] == 0)
		{
			return false;
		}
	}
	return true;
}

void Game::check_collisions()
{
	const int spot = CollisionDetector::check_collisions_spots(player);
	if (spot != -1)
	{
		if (spots_[spot] == 1)
		{
			fail();
		}
		else
		{
			spots_[spot] = 1;
			success();
		}
	}

	CollisionDetector::check_collisions_water(player, logs, logs_amt_, tortoises, tortoises_amt_);
	if (CollisionDetector::check_collisions_car(player, cars, cars_amt_))
	{
		fail();
	}

	if (CollisionDetector::check_collision_border(player))
	{
		fail();
	}
}

void Game::update_entities()
{
	player->update();
	
	for (int i = 0; i < cars_amt_; i++)
	{
		cars[i]->update();
	}

	for (int i = 0; i < logs_amt_; i++)
	{
		logs[i]->update();
	}

	for (int i = 0; i < tortoises_amt_; i++)
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
		window_ = SDL_CreateWindow(title, x_pos, y_pos, SCREEN_WIDTH, SCREEN_HEIGHT, flags);

		if (window_ == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			printf("Window initialized!\n");
			Global::renderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

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
	for (int i = 0; i < cars_amt_; i++)
	{
		cars[i]->render();
	}
	for (int i = 0; i < logs_amt_; i++)
	{
		logs[i]->render();
	}
	for (int i = 0; i < tortoises_amt_; i++)
	{
		tortoises[i]->render();
	}

	player->render();
}

void Game::render_spots()
{
	for (int i = 0; i < spots_amt_; i++)
	{
		if (spots_[i] == 1)
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
	
	for (int i = 0; i < cars_amt_; i++)
	{
		SDL_DestroyTexture(cars[i]->get_texture());
	}
	for (int i = 0; i < logs_amt_; i++)
	{
		SDL_DestroyTexture(logs[i]->get_texture());
	}
	for (int i = 0; i < tortoises_amt_; i++)
	{
		SDL_DestroyTexture(tortoises[i]->get_texture());
	}

	delete player;
	for (int i = 0; i < cars_amt_; i++)
	{
		delete cars[i];
	}
	for (int i = 0; i < logs_amt_; i++)
	{
		delete logs[i];
	}
	for (int i = 0; i < tortoises_amt_; i++)
	{
		delete tortoises[i];
	}

	free(player_s_);
	free(cars_s_);
	free(logs_s_);
	free(tortoises_s_);
}

void Game::create_entities()
{
	player = new Player(player_s_);
	create_cars();
	create_logs();
	create_tortoises();
}
