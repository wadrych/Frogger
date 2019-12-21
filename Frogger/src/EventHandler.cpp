#include "EventHandler.h"

void EventHandler::move_right(Player* p, Map* m)
{
	p->move_x(32);
	if(p->get_dest_rect().x + p->get_dest_rect().w >= m->get_dest_rect().w)
	{
		p->move_x(-32);
	}
}

void EventHandler::move_left(Player* p, Map* m)
{
	p->move_x(-32);
	if (p->get_dest_rect().x <= 0)
	{
		p->move_x(32);
	}
}

void EventHandler::move_down(Player* p, Map* m)
{
	p->move_y(32);
	if (p->get_dest_rect().y + p->get_dest_rect().h >= m->get_dest_rect().h)
	{
		p->move_y(-32);
	}
}

void EventHandler::move_up(Player* p, Map* m)
{
	p->move_y(-32);
	if (p->get_dest_rect().y <=0)
	{
		p->move_y(32);
	}
}

bool EventHandler::check_collisions(Player* p, Car* car_1[])
{
	for (int i = 0; i < 5; i++)
	{
		if (CollisonDetector::check_collision(p->get_dest_rect(), car_1[i]->get_dest_rect()))
		{
			return true;
		}
	}
	return false;
}



