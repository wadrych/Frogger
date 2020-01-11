#include "EventHandler.h"
#include "Game.h"


void EventHandler::move_right(Map* m)
{
	Player* p = EntitiyManager::player;
	
	p->move_right();
	if(p->get_dest_rect().x + p->get_dest_rect().w >= m->get_dest_rect().w && p->get_dest_rect().y >= 192)//192 pixel - beggining of route)
	{
		p->move_left();
		
		if(p->has_frog())
		{
			EntitiyManager::bonus_frog->move_left();
		}
	}
}

void EventHandler::move_left(Map* m)
{
	Player* p = EntitiyManager::player;
	
	p->move_left();
	if (p->get_dest_rect().x <= 0 && p->get_dest_rect().y >= 192)//192 pixel - beginning of route
	{
		p->move_right();
		
		if (p->has_frog())
		{
			EntitiyManager::bonus_frog->move_right();
		}
	}
}

void EventHandler::move_down(Map* m)
{
	Player* p = EntitiyManager::player;
	
	p->move_down();
	if (p->get_dest_rect().y + p->get_dest_rect().h >= m->get_dest_rect().h)
	{
		p->move_up();
		
		if (p->has_frog())
		{
			EntitiyManager::bonus_frog->move_up();
		}
	}
}

void EventHandler::move_up(Map* m)
{
	Player* p = EntitiyManager::player;
	
	p->move_up();
	if (p->get_dest_rect().y <=0)
	{
		p->move_down();

		if (p->has_frog())
		{
			EntitiyManager::bonus_frog->move_down();
		}
	}
}

void EventHandler::quit_game(bool* is_running)
{
	*is_running = false;
}

void EventHandler::restart_game(option* current, int spots[], EntitiyManager* entity_manager, double* world_time, int* score)
{
	Player* p = EntitiyManager::player;
	
	p->init();
	
	*score = 0;
	*current = GAME;
	*world_time = 0;
	for(int i = 0; i < 5; i++)
	{
		spots[i] = 0;
	}
	entity_manager->destroy();
	entity_manager->init();
	
}

void EventHandler::pause_game(option* current)
{
	if(*current == PAUSE)
	{
		*current = GAME;
	}
	else if (*current == GAME)
	{
		*current = PAUSE;
	}
}

void EventHandler::quit_menu(option* current)
{
	if (*current == QUIT)
	{
		*current = GAME;
	}
	else if (*current == GAME)
	{
		*current = QUIT;
	}
}

void EventHandler::menu_up(option* current)
{
	if(*current == NEW_GAME)
	{
		*current = QUIT_GAME;
	}
	else if(*current == HIGH_SCORES)
	{
		*current = NEW_GAME;
	}
	else if (*current == QUIT_GAME)
	{
		*current = HIGH_SCORES;
	}
}

void EventHandler::menu_down(option* current)
{
	if (*current == NEW_GAME)
	{
		*current = HIGH_SCORES;
	}
	else if (*current == HIGH_SCORES)
	{
		*current = QUIT_GAME;
	}
	else if (*current == QUIT_GAME)
	{
		*current = NEW_GAME;
	}
}

void EventHandler::menu_launch(option* current, bool* is_running)
{
	if(*current == NEW_GAME)
	{
		*current = GAME;
	}
	else if (*current == HIGH_SCORES)
	{
		*current = HIGH_SCORES_TABLE;
	}
	else if (*current == QUIT_GAME)
	{
		quit_game(is_running);
	}
}

void EventHandler::handle_text_input(char name[8], SDL_bool* done)
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_TEXTINPUT:
			/* Add new text onto the end of our text */
			if (strlen(name) < 7)
			{
				strcat(name, event.text.text);
			}
			break;
		case SDL_KEYDOWN:
			char keyDown = event.key.keysym.scancode;

			if (keyDown == SDL_SCANCODE_BACKSPACE)
			{
				if (strlen(name) > 0)
				{
					name[strlen(name) - 1] = 0;
				}
			}
			else if (keyDown == SDL_SCANCODE_RETURN)
			{
				*done = SDL_TRUE;
			}
			break;
		}
	}
}

