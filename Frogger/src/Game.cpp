#include "Game.h"

SDL_Renderer* Global::renderer = NULL;
TTF_Font* Global::font = NULL;

Player* EntityManager::player;
GameObject** EntityManager::cars;
GameObject** EntityManager::logs;
Tortoise** EntityManager::tortoises;
BonusFrog* EntityManager::bonus_frog;
BonusBee* EntityManager::bonus_bee;

Game::Game()
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
}

Game::~Game()
{
}

void Game::init(const char* title, const int x_pos, const int y_pos)
{
	srand(time(NULL));
	
	is_running_ = sdl_initialization(title, x_pos, y_pos);

	set_renderer_conf();
	SDL_ShowCursor(SDL_DISABLE);
	
	last_frame_time_ = SDL_GetTicks();//Init of world time

	create_map();
	create_gui();
	
	entity_manager_ = new EntityManager();
	entity_manager_->init();

	last_position_ = (int)EntityManager::player->get_y();
	
	score_manager_ = new ScoreManager();
	score_manager_->init();
}

void Game::update()
{
	if (current_ == GAME)                  game_continue();
	else if(current_ == START_GAME)        start();
	else if(current_ == HIGH_SCORES_TABLE) gui_->show_high_scores(score_manager_->get_results(), score_manager_->get_results_amt());
	else                                   gui_->update_menu(current_);
}

void Game::render()
{
	SDL_RenderClear(Global::renderer);

	map_->render();

	render_spots();
	entity_manager_->render();
	
	gui_->render();

	SDL_RenderPresent(Global::renderer);
}

void Game::clean()
{
	SDL_DestroyTexture(screen_);
	screen_ = NULL;

	gui_->destroy();

	SDL_DestroyTexture(map_->get_texture());

	SDL_DestroyRenderer(Global::renderer);
	Global::renderer = NULL;

	SDL_DestroyWindow(window_);
	window_ = NULL;
	
	delete gui_;
	delete map_;
	delete score_manager_;
	
	entity_manager_->destroy();
	delete entity_manager_;

	SDL_Quit();

	printf("Game cleaned\n");
}

void Game::handle_events()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_UP)          EventHandler::arrow_up(&current_, map_);
		else if (event.key.keysym.sym == SDLK_DOWN)   EventHandler::arrow_down(&current_, map_);
		else if (event.key.keysym.sym == SDLK_LEFT)   EventHandler::arrow_left(current_, map_);
		else if (event.key.keysym.sym == SDLK_RIGHT)  EventHandler::arrow_right(current_, map_);
		else if (event.key.keysym.sym == SDLK_y)      EventHandler::key_y(&current_, &is_running_);
		else if (event.key.keysym.sym == SDLK_n)      EventHandler::key_n(&current_, &is_running_, gui_, &last_frame_time_);
		else if (event.key.keysym.sym == SDLK_p)      EventHandler::key_p(&current_, &last_frame_time_, gui_);
		else if (event.key.keysym.sym == SDLK_q)      EventHandler::key_q(&current_, &last_frame_time_, gui_);
		else if (event.key.keysym.sym == SDLK_RETURN) EventHandler::key_enter(&current_, gui_, &is_running_);
		break;

	case SDL_KEYUP:
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
	fps_timer_ += delta_s_;
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

	delta_ms_ = (current_frame_time_ - last_frame_time_);
	delta_s_ = delta_ms_ * to_seconds;
	last_frame_time_ = current_frame_time_;

	world_time_ += delta_s_;
}

void Game::create_gui()
{
	gui_ = new UserInterface;
	gui_->init(GUI_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::create_map()
{
	const int map_height = SCREEN_HEIGHT - GUI_HEIGHT;
	map_ = new Map;
	map_->init(SCREEN_WIDTH, map_height);
}

void Game::set_renderer_conf()
{
	SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, 255);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(Global::renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::fail()
{
	const int current_position = (int)EntityManager::player->get_y();

	//Add points if last position is higher than latter
	if(last_position_ > current_position)
	{
		score_ += 10;
		last_position_ = current_position;
	}

	//drop frog
	if(EntityManager::player->has_frog())
	{
		EntityManager::bonus_frog->set_visible(false);
	}

	//reset bee occurrence
	EntityManager::bonus_bee->reset();

	//reset player
	EntityManager::player->lost();
	EntityManager::player->reset_pos();

	//decide if game over
	if(!EntityManager::player->is_alive())
	{
		handle_score();
		current_ = GAME_OVER;
	}

	world_time_ = 0;
}

void Game::success(int spot)
{
	bonus_ = 0;

	//reserve the spot
	spots_[spot] = 1;
	EntityManager::bonus_bee->take_spot(spot);
	
	//Add points for bee
	if(CollisionDetector::caught_bee())
	{
		bonus_ += 200;
	}
	EntityManager::bonus_bee->set_visible(false);
	EntityManager::bonus_bee->reset();

	//Add points for frog
	if(EntityManager::player->has_frog())
	{
		bonus_ += 200;
		EntityManager::bonus_frog->set_visible(false);
	}
	EntityManager::player->lose_frog();

	score_ += bonus_;

	//Add points for time
	score_ += 50 + (int)((GAME_TIME - world_time_) * 10);
	
	EntityManager::player->reset_pos();

	//Check if won
	if(check_if_won())
	{
		handle_score();
		current_ = START_GAME;
	}
	
	world_time_ = 0;
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

	SDL_bool done = SDL_FALSE;

	if(score_manager_->is_higher_than_saved(score_))
	{
		SDL_StartTextInput();
		while (!done)
		{
			EventHandler::handle_text_input(name, &done);
			gui_->show_save_score(score_, name);
			render();
		}
		score_manager_->set_new_high_score(score_, name);
	}
}

void Game::handle_collisions()
{
	const int spot = CollisionDetector::check_collisions_spots();
	if (spot != -1)
	{
		if (spots_[spot] == 1) fail();
		else                   success(spot);
	}

	if(CollisionDetector::check_collision(EntityManager::player->get_dest_rect(), EntityManager::bonus_frog->get_dest_rect())  && EntityManager::bonus_frog->is_visible())
	{
		EntityManager::bonus_frog->set_velocity(0);
		EntityManager::player->attach_frog();
	}

	if(EntityManager::player->has_frog())
	{
		EntityManager::bonus_frog->set_x(EntityManager::player->get_x());
		EntityManager::bonus_frog->set_y(EntityManager::player->get_y());
	}

	CollisionDetector::check_collisions_water();
	
	if (CollisionDetector::check_collisions_car()) fail();

	if (CollisionDetector::check_collision_border()) fail();
}

bool Game::sdl_initialization(const char* title, const int x_pos, const int y_pos)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		printf("SDL initialized!\n");
		window_ = SDL_CreateWindow(title, x_pos, y_pos, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

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
						Global::font = TTF_OpenFont("../../TTF/VT323-Regular.ttf", 100);
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
			SDL_RenderCopy(Global::renderer, EntityManager::player->get_texture(), &(EntityManager::player->get_src_rect()), &temp);
		}
	}
}

void Game::check_time()
{
	if(world_time_ > GAME_TIME)
	{
		fail();
	}
}

void Game::game_continue()
{
	calculate_time();
	check_time();

	entity_manager_->update(delta_ms_);

	handle_collisions();

	EntityManager::player->update(); //if position of player was changed due to detected collisions apply the changes

	if (bonus_ > 0)
	{
		render();
		gui_->show_bonus(EntityManager::player->get_dest_rect(), bonus_);
		bonus_ = 0;
	}

	fps_counter();

	gui_->update_info(world_time_, fps_, EntityManager::player->health(), score_);

	frames_++;
}

void Game::start()
{
	last_frame_time_ = SDL_GetTicks();//Init of world time

	create_map();
	create_gui();

	last_position_ = (int)EntityManager::player->get_y();

	EntityManager::player->init();

	score_ = 0;
	current_ = GAME;
	world_time_ = 0;
	for (int i = 0; i < 5; i++)
	{
		spots_[i] = 0;
	}
	entity_manager_->destroy();
	entity_manager_->init();
}
