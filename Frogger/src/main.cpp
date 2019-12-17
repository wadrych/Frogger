#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Game.h"
#include "SDL.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480   

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv)
{
	const char* title = "Frogger - Wojciech Adrych 2019";
	const bool fullscreen = false;

	const int second = 1000;
	const int frame_per_second = 60;
	const int avg_frame_time = second / frame_per_second;
	Uint32 frame_start;
	int frame_time;

	Game* game = new Game;

	game->init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen);


	while (game->running())
	{
		frame_start = SDL_GetTicks();

		game->handle_evnets();
		game->update();
		game->render();


		//Framerate capping
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_time < avg_frame_time)
		{
			SDL_Delay(avg_frame_time - frame_time);
		}

	}

	game->clean();

	delete game;
	/*
	int t1, t2, quit, frames;

	double delta, world_time, fps_timer, fps, distance, eti_speed;

	SDL_Event event;
	SDL_Surface* screen    = NULL;
	SDL_Surface* charset   = NULL;
	SDL_Surface *eti       = NULL;
	SDL_Texture *scrtex    = NULL;
	SDL_Window *window     = NULL;
	SDL_Renderer *renderer = NULL;
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if (!init(&window, &renderer, &screen, &scrtex, false))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if ( !load_media(&charset, &eti) )
		{
			printf("Failed to load media!\n");
		}
		else
		{
			char text[128];
			int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
			int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
			int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
			int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
			t1 = SDL_GetTicks();
			frames = 0;
			fps_timer = 0;
			fps = 0;
			quit = 0;
			world_time = 0;
			distance = 0;
			eti_speed = 1;
			while (!quit) {
				t2 = SDL_GetTicks();
				// here t2-t1 is the time in milliseconds since
				// the last screen was drawn
				// delta is the same time in seconds
				delta = (t2 - t1) * 0.001;
				t1 = t2;
				world_time += delta;
				distance += eti_speed * delta;
				SDL_FillRect(screen, NULL, black);
				DrawSurface(screen, eti,
					SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3,
					SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3);
				fps_counter(&fps_timer, &fps, &frames, delta);
				show_info_text(screen,text, blue, red, world_time, fps, charset);
				// _TODO__
				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				//		SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
				//

				// Event handler
				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						else if (event.key.keysym.sym == SDLK_UP) eti_speed = 2.0;
						else if (event.key.keysym.sym == SDLK_DOWN) eti_speed = 0.3;
						break;
					case SDL_KEYUP:
						eti_speed = 1.0;
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				};
				frames++;
			};
		}
	}

	//Clean up
	close(&screen, &charset, &scrtex, &window, &renderer);
*/
	return 0;
};