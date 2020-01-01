#include "Game.h"

SDL_Renderer* Global::renderer = NULL;
TTF_Font* Global::font = NULL;
long long int Global::time_delta = 0;

Player* EntitiyManager::player;
GameObject** EntitiyManager::cars;
GameObject** EntitiyManager::logs;
Tortoise** EntitiyManager::tortoises;
BonusFrog* EntitiyManager::bonus_frog;

game_object* EntitiyManager::player_s;
game_object* EntitiyManager::cars_s;
game_object* EntitiyManager::logs_s;
game_object* EntitiyManager::tortoises_s;
game_object* EntitiyManager::bonus_frog_s;


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
	score_ = 0;
	current_ = NEW_GAME;

	srand(time(NULL));
	
	is_running_ = sdl_initialization(title, x_pos, y_pos, fullscreen);

	set_renderer_conf();
	SDL_ShowCursor(SDL_DISABLE);
	
	last_frame_time_ = SDL_GetTicks();//Init of world time

	create_map();
	create_gui();
	
	entitiy_manager_ = new EntitiyManager();
	entitiy_manager_->init();

	score_manager = new ScoreManager();
	score_manager->init();

	last_position_ = (int)EntitiyManager::player->get_y();
}

void Game::update()
{
	if (current_ == GAME)//!game_over_ && !paused_ && !quit_ && !main_menu_)
	{
		calculate_time();
		check_time();

		entitiy_manager_->update();

		check_collisions();

		if (bonus_ > 0)
		{
			render();
			gui->show_bonus(EntitiyManager::player->get_dest_rect(), bonus_);
			bonus_ = 0;
		}
		

		EntitiyManager::player->update(); //if position of player was changed due to detected collisions apply the changes

		fps_counter();

		gui->update_info(world_time_, fps_, EntitiyManager::player->health(), score_);
		
		frames_++;
	}
	else if(current_ == HIGH_SCORES_TABLE)
	{
		gui->show_high_scores(score_manager->get_results(), score_manager->get_results_amt());
	}
	else
	{
		gui->update_menu(current_);
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

	gui->destroy();

	SDL_DestroyTexture(map->get_texture());

	SDL_DestroyRenderer(Global::renderer);
	Global::renderer = NULL;

	SDL_DestroyWindow(window_);
	window_ = NULL;

	
	delete gui;
	delete map;
	delete score_manager;
	
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
		else if (event.key.keysym.sym == SDLK_UP)
		{
			if(current_ == NEW_GAME || current_ == HIGH_SCORES || current_ == QUIT_GAME)
			{
				EventHandler::menu_up(&current_);
			}
			else if (current_ == GAME)
			{
				EventHandler::move_up(map);
			}
		}
		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			if (current_ == NEW_GAME || current_ == HIGH_SCORES || current_ == QUIT_GAME)
			{
				EventHandler::menu_down(&current_);
			}
			else if(current_ == GAME)
			{
				EventHandler::move_down(map);
			}
		}
		else if (event.key.keysym.sym == SDLK_LEFT && current_ == GAME) EventHandler::move_left(map);
		else if (event.key.keysym.sym == SDLK_RIGHT && current_ ==  GAME) EventHandler::move_right(map);
		else if (event.key.keysym.sym == SDLK_y)
		{
			if(current_ == GAME_OVER)
			{
				EventHandler::quit_game(&is_running_);
			}
			else if (current_ == QUIT)
			{
				current_ = NEW_GAME;
			}
		}
		else if (event.key.keysym.sym == SDLK_n)
		{
			if(current_ == QUIT)
			{
				EventHandler::quit_menu(&current_);
				last_frame_time_ = SDL_GetTicks();
				gui->clean_menu();
			}
			else if(current_ == GAME_OVER)
			{
				EventHandler::restart_game(&current_, spots_, entitiy_manager_, &world_time_, &score_);
				gui->clean_menu();
				last_frame_time_ = SDL_GetTicks();
				last_position_= (int)EntitiyManager::player->get_y();
				score_ = 0;
			}
		}
		else if (event.key.keysym.sym == SDLK_p && ( current_ == GAME || current_ == PAUSE))
		{
			last_frame_time_ = SDL_GetTicks();
			EventHandler::pause_game(&current_);
			gui->clean_menu();
		}
		else if (event.key.keysym.sym == SDLK_q)
		{
			if(current_ == HIGH_SCORES_TABLE)
			{
				current_ = NEW_GAME;
			}
			else if (current_ == GAME || current_ == QUIT)
			{
				EventHandler::quit_menu(&current_);
				last_frame_time_ = SDL_GetTicks();
				gui->clean_menu();
			}
		}
		else if (event.key.keysym.sym == SDLK_RETURN)
		{
			if (current_ == NEW_GAME)
			{
				EventHandler::restart_game(&current_, spots_, entitiy_manager_, &world_time_, &score_);
			}
			EventHandler::menu_launch(&current_, &is_running_);
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

	world_time_ += delta_*5;
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
	const int current_position = (int)EntitiyManager::player->get_y();

	if(last_position_ > current_position)
	{
		score_ += 10;
		last_position_ = current_position;
	}

	if(EntitiyManager::player->has_bonus())
	{
		EntitiyManager::bonus_frog->set_visible(false);
	}
	
	EntitiyManager::player->lost();
	EntitiyManager::player->set_x(EntitiyManager::player_s->x);
	EntitiyManager::player->set_y(EntitiyManager::player_s->y);

	if(!EntitiyManager::player->is_alive())
	{
		handle_score();
		current_ = GAME_OVER;
	}
	world_time_ = 0;
}

void Game::success()
{
	const int game_time = 50;
	bonus_ = 0;
	EntitiyManager::player->set_x(EntitiyManager::player_s->x);
	EntitiyManager::player->set_y(EntitiyManager::player_s->y);
	
	score_ += 50 + (int)((game_time-world_time_) * 10);

	if(EntitiyManager::player->has_bonus())
	{
		bonus_ += 200;
		EntitiyManager::bonus_frog->set_visible(false);
	}
	EntitiyManager::player->lose_bonus();
	
	score_ += bonus_;
	
	world_time_ = 0;
	
	if(check_if_won())
	{
		handle_score();
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

void Game::handle_score()
{	
	char name[8] = "";
	char* composition;
	Sint32 cursor;
	Sint32 selection_len;

	SDL_bool done = SDL_FALSE;

	if(score_manager->is_higher_than_saved(score_))
	{
		SDL_StartTextInput();
		while (!done)
		{
			EventHandler::handle_text_input(name, &done);
			gui->show_save_score(score_, name);
			render();
		}
		score_manager->set_new_high_score(score_, name);
	}
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

	if(CollisionDetector::check_collision(EntitiyManager::player->get_dest_rect(), EntitiyManager::bonus_frog->get_dest_rect())  && EntitiyManager::bonus_frog->is_visible())
	{
		EntitiyManager::bonus_frog->set_velocity(0);
		EntitiyManager::player->attach_bonus();
		
	}

	if(EntitiyManager::player->has_bonus())
	{
		EntitiyManager::bonus_frog->set_x(EntitiyManager::player->get_x());
		EntitiyManager::bonus_frog->set_y(EntitiyManager::player->get_y());
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
