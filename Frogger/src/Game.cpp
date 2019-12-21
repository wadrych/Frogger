#include "Game.h"

SDL_Renderer* Global::renderer = NULL;
TTF_Font* Global::font = NULL;

UserInterface* gui;
Map* map;
Player* player;
Car* car_1[5];

Game::Game(int width, int height, int gui_h) : screen_width( width ), screen_height( height ), gui_height( gui_h )
{
	frames = 0;
	fps_timer = 0;
	fps = 0;
	world_time = 0;
	distance = 0;
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
		window = SDL_CreateWindow(title, xpos, ypos, screen_width, screen_height, flags);

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

							create_map(screen_height - gui_height);

							create_gui(gui_height);
							
							player = new Player("assets/frog.png", 224 ,384);
							car_1[0] = new Car("assets/car_1.png", 0, 352, 5, screen_width);
							car_1[1] = new Car("assets/car_1.png", screen_width /2 , 352, 5, screen_width);
							car_1[2] = new Car("assets/car_1.png", screen_width, 352, 5, screen_width);
							car_1[3] = new Car("assets/car_1.png", -screen_width / 2, 352, 5, screen_width);
							car_1[4] = new Car("assets/car_1.png", -screen_width, 352, 5, screen_width);
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

	for(int i =0;i<5;i++)
	{
		car_1[i]->update((int)world_time);
	}

	if(EventHandler::check_collisions(player, car_1))
	{
		player->update_x(224);
		player->update_y(384);
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
	
	for (int i = 0; i < 5; i++)
	{
		car_1[i]->render();
	}
	player->render();

	SDL_RenderPresent(Global::renderer);
}

void Game::clean()
{
	//Deallocate all surfaces
	SDL_FreeSurface(charset);
	charset = NULL;

	//Destroy Texture
	SDL_DestroyTexture(screen);
	screen = NULL;

	SDL_DestroyTexture(gui->get_texture());
	
	SDL_DestroyTexture(gui->get_texture_text());

	SDL_DestroyTexture(map->get_texture());
	
	SDL_DestroyTexture(player->get_texture());

	for (int i = 0; i < 5; i++)
	{
		SDL_DestroyTexture(car_1[i]->get_texture());
	}

	//Destroy renderer
	SDL_DestroyRenderer(Global::renderer);
	Global::renderer = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	
	//Delete objects
	delete gui;
	delete map;
	delete player;
	for (int i = 0; i < 5; i++)
	{
		delete car_1[i];
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

void Game::create_gui(int gui_height)
{
	gui = new UserInterface;
	gui->init(gui_height, screen_width, screen_height);
}

void Game::create_map(int map_height)
{
	map = new Map;
	map->init(screen_width, map_height);
}

void Game::set_renderer_conf()
{
	SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, 255);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(Global::renderer, screen_width, screen_height);
}


