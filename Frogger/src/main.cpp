#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Game.h"
#include "SDL.h"

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

	Game* game = new Game();

	game->init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, fullscreen);


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
	
	return 0;
};