#include "EventHandler.h"

void EventHandler::move_right(Player* p, Map* m)
{
	p->move_right();
	if(p->get_dest_rect().x + p->get_dest_rect().w >= m->get_dest_rect().w && p->get_dest_rect().y >= 192)//192 pixel - beggining of route)
	{
		p->move_left();
	}
}

void EventHandler::move_left(Player* p, Map* m)
{
	p->move_left();
	if (p->get_dest_rect().x <= 0 && p->get_dest_rect().y >= 192)//192 pixel - beggining of route
	{
		p->move_right();
	}
}

void EventHandler::move_down(Player* p, Map* m)
{
	p->move_down();
	if (p->get_dest_rect().y + p->get_dest_rect().h >= m->get_dest_rect().h)
	{
		p->move_up();
	}
}

void EventHandler::move_up(Player* p, Map* m)
{
	p->move_up();
	if (p->get_dest_rect().y <=0)
	{
		p->move_down();
	}
}