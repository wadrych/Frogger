#include "Game.h"

SDL_Renderer* Global::renderer = NULL;
TTF_Font* Global::font = NULL;
long long int Global::time_delta = 0;

Player* EntitiyManager::player;
GameObject** EntitiyManager::cars;
GameObject** EntitiyManager::logs;
Tortoise** EntitiyManager::tortoises;

game_object* EntitiyManager::player_s;
game_object* EntitiyManager::cars_s;
game_object* EntitiyManager::logs_s;
game_object* EntitiyManager::tortoises_s;

UserInterface* gui;
Map* map;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, const int x_pos, const int y_pos, const bool fullscreen)
{
	frames_ = 0;
	fps_timer_ = 0;
	fps_ = 0;
	world_time_ = 0;
	spots_[0] = 0;
	spots_[1] = 0;
	spots_[2] = 0;
	spots_[3] = 0;
	spots_[4] = 0;
	spots_amt_ = 5;
	game_over_ = false;
	paused_ = false;
	quit_ = false;
	
	srand(time(NULL));
	
	is_running_ = sdl_initialization(title, x_pos, y_pos, fullscreen);

	set_renderer_conf();
	SDL_ShowCursor(SDL_DISABLE);
	
	last_frame_time_ = SDL_GetTicks();//Init of world time

	create_map();
	create_gui();
	
	entitiy_manager_ = new EntitiyManager();
	entitiy_manager_->init();
}

void Game::update()
{
	if(!game_over_ && !paused_ && !quit_)
	{
		calculate_time();
		check_time();

		entitiy_manager_->update();

		check_collisions();

		EntitiyManager::player->update(); //if position of player was changed due to detected collisions apply the changes

		fps_counter();

		gui->update_info(world_time_, fps_, EntitiyManager::player->health());

		frames_++;
	}
	else if(game_over_)
	{
		gui->update_menu(GAME_OVER);
	}
	else if(paused_)
	{
		gui->update_menu(PAUSE);
	}
	else if(quit_)
	{
		gui->update_menu(QUIT);
	}
}

void Game::render()
{
	SDL_RenderClear(Global::renderer);

	map->render();

	render_spots();
	entitiy_manager_->render();
	
	gui->render();

	SDL_RenderPresent(Global::renderer);
}

void Game::clean()
{
	SDL_DestroyTexture(screen_);
	screen_ = NULL;

	SDL_DestroyTexture(gui->get_texture());
	
	SDL_DestroyTexture(gui->get_texture_text());

	SDL_DestroyTexture(gui->get_menu_texture());

	SDL_DestroyTexture(map->get_texture());

	SDL_DestroyRenderer(Global::renderer);
	Global::renderer = NULL;

	SDL_DestroyWindow(window_);
	window_ = NULL;

	
	delete gui;
	delete map;
	
	entitiy_manager_->destroy();
	delete entitiy_manager_;
	

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
		else if (event.key.keysym.sym == SDLK_UP) EventHandler::move_up(map);
		else if (event.key.keysym.sym == SDLK_DOWN) EventHandler::move_down(map);
		else if (event.key.keysym.sym == SDLK_LEFT) EventHandler::move_left(map);
		else if (event.key.keysym.sym == SDLK_RIGHT) EventHandler::move_right(map);
		else if (event.key.keysym.sym == SDLK_y && (game_over_ || quit_)) EventHandler::quit_game(&is_running_);
		else if (event.key.keysym.sym == SDLK_n && (game_over_ || quit_))
		{
			if(quit_)
			{
				EventHandler::quit_menu(&quit_);
			}
			else
			{
				EventHandler::restart_game(&game_over_, spots_, entitiy_manager_, &world_time_);
				gui->clean_menu();
				last_frame_time_ = SDL_GetTicks();
			}
		}
		else if (event.key.keysym.sym == SDLK_p && !game_over_ && !quit_)
		{
			EventHandler::pause_game(&paused_);
			gui->clean_menu();
		}
		else if (event.key.keysym.sym == SDLK_q && !game_over_ && !paused_)
		{
			EventHandler::quit_menu(&quit_);
			gui->clean_menu();
		}
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
	SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, 255);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(Global::renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::fail()
{
	EntitiyManager::player->lost();
	EntitiyManager::player->set_x(EntitiyManager::player_s->x);
	EntitiyManager::player->set_y(EntitiyManager::player_s->y);

	if(!EntitiyManager::player->is_alive())
	{
		game_over_ = true;
	}
	world_time_ = 0;
}

void Game::success()
{
	EntitiyManager::player->set_x(EntitiyManager::player_s->x);
	EntitiyManager::player->set_y(EntitiyManager::player_s->y);

	if(check_if_won())
	{
		
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
	const int spot = CollisionDetector::check_collisions_spots();
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

	CollisionDetector::check_collisions_water();
	if (CollisionDetector::check_collisions_car())
	{
		fail();
	}

	if (CollisionDetector::check_collision_border())
	{
		fail();
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
						Global::font = TTF_OpenFont("../../TTF/UniversCondensed.ttf", 100);
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
			SDL_RenderCopy(Global::renderer, EntitiyManager::player->get_texture(), &(EntitiyManager::player->get_src_rect()), &temp);
		}
	}
}

void Game::check_time()
{
	const double game_time = 50;

	if(world_time_ > game_time)
	{
		fail();
	}
}
