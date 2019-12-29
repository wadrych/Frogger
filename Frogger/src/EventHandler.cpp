#include "EventHandler.h"


void EventHandler::move_right(Map* m)
{
	Player* p = EntitiyManager::player;
	
	p->move_right();
	if(p->get_dest_rect().x + p->get_dest_rect().w >= m->get_dest_rect().w && p->get_dest_rect().y >= 192)//192 pixel - beggining of route)
	{
		p->move_left();
	}
}

void EventHandler::move_left(Map* m)
{
	Player* p = EntitiyManager::player;
	
	p->move_left();
	if (p->get_dest_rect().x <= 0 && p->get_dest_rect().y >= 192)//192 pixel - beginning of route
	{
		p->move_right();
	}
}

void EventHandler::move_down(Map* m)
{
	Player* p = EntitiyManager::player;
	
	p->move_down();
	if (p->get_dest_rect().y + p->get_dest_rect().h >= m->get_dest_rect().h)
	{
		p->move_up();
	}
}

void EventHandler::move_up(Map* m)
{
	Player* p = EntitiyManager::player;
	
	p->move_up();
	if (p->get_dest_rect().y <=0)
	{
		p->move_down();
	}
}

void EventHandler::quit_game(bool* is_running)
{
	*is_running = false;
}

void EventHandler::restart_game(bool* game_over, int spots[], EntitiyManager* entity_manager, double* world_time)
{
	Player* p = EntitiyManager::player;
	
	p->init();
	*game_over = false;
	*world_time = 0;
	for(int i = 0; i < 5; i++)
	{
		spots[i] = 0;
	}
	entity_manager->destroy();
	entity_manager->init();
}

void EventHandler::pause_game(bool* paused)
{
	*paused = !*paused;
}

void EventHandler::quit_menu(bool* quit)
{
	*quit = !*quit;
}
