#include "EventHandler.h"
#include "Game.h"


void EventHandler::move_right(Map* m)
{
	Player* p = EntityManager::player;
	const int beginning_of_road = 192 + 16;
	
	p->move_right();
	if(p->get_x() + p->get_dest_rect().w > m->get_dest_rect().w && p->get_y() >= beginning_of_road)
	{
		p->move_left();
	}
}

void EventHandler::move_left(Map* m)
{
	Player* p = EntityManager::player;
	const int beginning_of_road = 192 + 16;
	
	p->move_left();
	if (p->get_x() < m->get_dest_rect().x && p->get_y() >= beginning_of_road)
	{
		p->move_right();
	}
}

void EventHandler::move_down(Map* m)
{
	Player* p = EntityManager::player;
	
	p->move_down();
	if (p->get_y() + p->get_dest_rect().h > m->get_dest_rect().h)
	{
		p->move_up();
	}
}

void EventHandler::move_up(Map* m)
{
	Player* p = EntityManager::player;
	
	p->move_up();
	if (p->get_y() < m->get_dest_rect().y)
	{
		p->move_down();
	}
}

void EventHandler::quit_game(bool* is_running)
{
	*is_running = false;
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
		*current = START_GAME;
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

void EventHandler::arrow_up(option* current, Map* map)
{
	if (*current == NEW_GAME || *current == HIGH_SCORES || *current == QUIT_GAME)
	{
		menu_up(current);
	}
	else if (*current == GAME)
	{
		move_up(map);
	}
}

void EventHandler::arrow_down(option* current, Map* map)
{
	if (*current == NEW_GAME || *current == HIGH_SCORES || *current == QUIT_GAME)
	{
		menu_down(current);
	}
	else if (*current == GAME)
	{
		move_down(map);
	}
}

void EventHandler::arrow_left(option current, Map* map)
{
	if(current == GAME)
	{
		move_left(map);
	}
}

void EventHandler::arrow_right(option current, Map* map)
{
	if (current == GAME)
	{
		move_right(map);
	}
}

void EventHandler::key_y(option* current, bool* is_running)
{
	if (*current == GAME_OVER)
	{
		EventHandler::quit_game(is_running);
	}
	else if (*current == QUIT)
	{
		*current = NEW_GAME;
	}
}

void EventHandler::key_n(option* current, bool* is_running, UserInterface* gui, Uint32* last_frame_time)
{
	if (*current == QUIT)
	{
		EventHandler::quit_menu(current);
		*last_frame_time = SDL_GetTicks();
		gui->clean_menu();
	}
	else if (*current == GAME_OVER)
	{
		*current = START_GAME;
	}
}

void EventHandler::key_p(option* current, Uint32* last_frame_time, UserInterface* gui)
{
	if(*current == GAME || *current == PAUSE)
	{
		*last_frame_time = SDL_GetTicks();
		EventHandler::pause_game(current);
		gui->clean_menu();
	}
}

void EventHandler::key_q(option* current, Uint32* last_frame_time, UserInterface* gui)
{
	if (*current == HIGH_SCORES_TABLE)
	{
		*current = NEW_GAME;
	}
	else if (*current == GAME || *current == QUIT)
	{
		EventHandler::quit_menu(current);
		*last_frame_time = SDL_GetTicks();
		gui->clean_menu();
	}
}

void EventHandler::key_enter(option* current, UserInterface* gui, bool* is_running)
{
	EventHandler::menu_launch(current, is_running);
	gui->clean_menu();
}




