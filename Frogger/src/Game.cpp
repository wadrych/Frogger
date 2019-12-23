#include "Game.h"

SDL_Renderer* Global::renderer = NULL;
TTF_Font* Global::font = NULL;

UserInterface* gui;
Map* map;
Player* player;
Car* cars[13];

Game::Game()
{
	frames = 0;
	fps_timer = 0;
	fps = 0;
	world_time = 0;
	cars_amt = 0;
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		is_running = false;
	}
	else
	{
		printf("SDL initialized!\n");
		window = SDL_CreateWindow(title, xpos, ypos, SCREEN_WIDTH, SCREEN_HEIGHT, flags);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			is_running = false;
		}
		else
		{
			printf("Window initialized!\n");
			Global::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (Global::renderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				is_running = false;
			}
			else
			{
				printf("Renderer initialized!\n");

				int imgFlags = IMG_INIT_PNG;
				
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					is_running = false;
				}
				else
				{
					printf("SDL_image initialized!\n");
					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						is_running = false;
					}
					else
					{
						printf("SDL_ttf initialized!\n");
						Global::font = TTF_OpenFont("../../TTF/UniversCondensed.ttf", 28);
						if (Global::font == NULL)
						{
							printf("Font could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
							is_running = false;
						}
						else
						{
							printf("Font initialized!\n");
							is_running = true;

							set_renderer_conf();

							create_map();

							create_gui();

							//loads initialization structs
							load_structs();

							create_player();

							create_cars();
							
							SDL_ShowCursor(SDL_DISABLE);

							//Init of world time
							last_frame_time = SDL_GetTicks();
						}
					}
				}
			}
		}
	}
}

void Game::update()
{
	calculate_time();

	player->update();

	for(int i =0; i < cars_amt; i++)
	{
		cars[i]->update((int)world_time);
	}

	if(CollisonDetector::check_collisions(player, cars, cars_amt))
	{
		player->set_x(player_s->x);
		player->set_y(player_s->y);
	}
	
	fps_counter();
	gui->update_info(world_time, fps);
	
	frames++;
}

void Game::render()
{
	SDL_RenderClear(Global::renderer);

	map->render();
	gui->render();
	
	for (int i = 0; i < cars_amt; i++)
	{
		cars[i]->render();
	}
	player->render();

	SDL_RenderPresent(Global::renderer);
}

void Game::clean()
{
	//Destroy Texture
	SDL_DestroyTexture(screen);
	screen = NULL;

	SDL_DestroyTexture(gui->get_texture());
	
	SDL_DestroyTexture(gui->get_texture_text());

	SDL_DestroyTexture(map->get_texture());
	
	SDL_DestroyTexture(player->get_texture());

	for (int i = 0; i < cars_amt; i++)
	{
		SDL_DestroyTexture(cars[i]->get_texture());
	}

	//Destroy renderer
	SDL_DestroyRenderer(Global::renderer);
	Global::renderer = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	
	//Delete objects
	free_structs();
	
	delete gui;
	delete map;
	delete player;
	for (int i = 0; i < cars_amt; i++)
	{
		delete cars[i];
	}

	//Quit SDL subsystems
	SDL_Quit();

	printf("Game cleaned\n");
}

void Game::handle_evnets()
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

	delta = (current_frame_time - last_frame_time) * to_seconds;
	last_frame_time = current_frame_time;

	world_time += delta;
}

void Game::create_gui()
{
	gui = new UserInterface;
	gui->init(GUI_HEIGHT, SCREEN_HEIGHT, SCREEN_HEIGHT);
}

void Game::create_map()
{
	int map_height = SCREEN_HEIGHT - GUI_HEIGHT;
	map = new Map;
	map->init(SCREEN_HEIGHT, map_height);
}

void Game::set_renderer_conf()
{
	SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, 255);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(Global::renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::create_cars()
{
	for (int i = 0; i < cars_amt; i++)
	{
		cars[i] = new Car(&cars_s[i]);
	}
}

void Game::load_structs()
{
	player_s = (game_object*)malloc(sizeof(game_object));
	*player_s = { 224 , 384, 32, 32,  "assets/frog.png", 0};

	cars_amt = 14;
	cars_s = (game_object*)malloc(cars_amt * sizeof(game_object));
	cars_s[0] = { 0, 352, 32, 32, "assets/car_1.png", -3 };
	cars_s[1] = { SCREEN_WIDTH / 2, 352, 32, 32, "assets/car_1.png", -3 };
	cars_s[2] = { SCREEN_WIDTH, 352, 32, 32, "assets/car_1.png", -3 };
	cars_s[3] = { SCREEN_WIDTH * 3 / 2, 352, 32, 32, "assets/car_1.png", -3 };
	cars_s[4] = { SCREEN_WIDTH, 224, 64, 32, "assets/car_1.png", 1 };
	cars_s[5] = { 0, 320, 32, 32, "assets/car_1.png", -1 }; 
	cars_s[6] = { SCREEN_WIDTH * 2 / 3, 320, 32, 32, "assets/car_1.png", -1 };
	cars_s[7] = { SCREEN_WIDTH * 2 * 2 / 3, 320, 32, 32, "assets/car_1.png", -1 };
	cars_s[8] = { SCREEN_WIDTH / 2, 288, 32, 32, "assets/car_1.png", 2 };
	cars_s[9] = { SCREEN_WIDTH, 288, 32, 32, "assets/car_1.png", 2 };
	cars_s[10] = { SCREEN_WIDTH * 3 / 2, 288, 32, 32, "assets/car_1.png", 2 };
	cars_s[11] = { SCREEN_WIDTH * 0, 288, 32, 32, "assets/car_1.png", 2 };
	cars_s[12] = { SCREEN_WIDTH, 256, 32, 32, "assets/car_1.png", -8 };
	cars_s[13] = { 0, 224, 64, 32, "assets/car_1.png", 1 };
	
}

void Game::create_player()
{
	player = new Player(player_s);
}

void Game::free_structs()
{
	free(player_s);
	free(cars_s);
}
