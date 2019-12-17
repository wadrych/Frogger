#include "Game.h"

SDL_Renderer* Game::renderer = NULL;

UserInterface* gui;
Map* map;

Game::Game()
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

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	screen_width = width;
	screen_height = height;

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
			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				is_running = false;
			}
			else
			{
				printf("Renderer initialized!\n");
				is_running = true;

				set_renderer_conf();

				const int gui_height = 26;

				create_map(screen_height - gui_height);

				create_gui(gui_height);
				
				SDL_ShowCursor(SDL_DISABLE);

				//Init of world time
				last_frame_time = SDL_GetTicks();
			}
		}
	}
}

void Game::update()
{
	calculate_time();

	fps_counter();

	
	SDL_DestroyTexture(gui_tex);
	gui_tex = gui->update_info(world_time, fps);
	
	frames++;
}

void Game::clean()
{
	//Delete graphics interface
	delete gui;

	//Deallocate all surfaces
	SDL_FreeSurface(charset);
	charset = NULL;

	//Destroy Texture
	SDL_DestroyTexture(screen);
	screen = NULL;

	SDL_DestroyTexture(gui_tex);
	gui_tex = NULL;

	SDL_DestroyTexture(map_tex);
	gui_tex = NULL;

	//Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

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
		else if (event.key.keysym.sym == SDLK_UP) ;
		else if (event.key.keysym.sym == SDLK_DOWN) ;
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

void Game::render()
{
	SDL_RenderClear(renderer);
	
	SDL_RenderCopy(renderer, map_tex, NULL, &map->get_destination_rect());
	SDL_RenderCopy(renderer, gui_tex, NULL, &gui->get_destination_rect());
	
	SDL_RenderPresent(renderer);
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
	gui = new UserInterface();
	if (!gui->init(gui_height, screen_width, screen_height))
	{
		printf("Couldn't load the info container");
	}
}

void Game::create_map(int map_height)
{
	map = new Map;
	map->init(screen_width, map_height);
	map_tex = map->get_texture();
}

void Game::set_renderer_conf()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, screen_width, screen_height);
}


