#include "Game.h"

Game::Game()
{
	frames = 0;
	fps_timer = 0;
	fps = 0;
	world_time = 0;
	distance = 0;
	eti_speed = 1;

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

		//Create window
		window = SDL_CreateWindow(title, xpos, ypos, screen_width, screen_height, flags);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			is_running = false;
		}
		else
		{
			printf("Window initialized!\n");
			//Create renderer
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

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
				SDL_RenderSetLogicalSize(renderer, screen_width, screen_height);

				screen = SDL_CreateRGBSurface(0, screen_width, screen_height, 32,
					0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

				scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
					SDL_TEXTUREACCESS_STREAMING,
					screen_width, screen_height);

				

				SDL_Surface* charset = NULL;
				charset = SDL_LoadBMP("assets/cs8x8.bmp");
				if (charset == NULL) {
					printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
				}
				else
				{
					SDL_SetColorKey(charset, true, 0x000000);

					gui = new UserInterface(screen, screen_height, screen_width, charset);
				}
				eti = SDL_LoadBMP("assets/eti.bmp");
				if (eti == NULL) {
					printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
				};


				black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
				green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
				red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
				blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

				//Cursor disabling
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

	distance += eti_speed * delta;
	SDL_FillRect(screen, NULL, blue);
	TextureManager::draw_surface(screen, eti,
		screen_width / 2 + sin(distance) * screen_height / 3,
		screen_height / 2 + cos(distance) * screen_height / 3);


	fps_counter();
	gui->info_text(world_time, fps);
	frames++;
}

void Game::clean()
{
	//Delete graphics interface
	delete gui;

	//Deallocate all surfaces
	SDL_FreeSurface(charset);
	charset = NULL;

	SDL_FreeSurface(screen);
	screen = NULL;

	//Destroy Texture
	SDL_DestroyTexture(scrtex);
	scrtex = NULL;

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
		else if (event.key.keysym.sym == SDLK_UP) eti_speed = 2.0;
		else if (event.key.keysym.sym == SDLK_DOWN) eti_speed = 0.3;
		break;

	case SDL_KEYUP:
		eti_speed = 1.0;
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
	//SDL_RenderClear(renderer);
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//There we're adding stuff to renderer
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
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

