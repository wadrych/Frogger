#include "Player.h"

Player::Player(game_object* rect) : GameObject(rect)
{
	start_x_ = rect->x;
	start_y_ = rect->y;
}

Player::~Player()
{
}

void Player::move_right()
{
	const int distance = 32;
	pos_x_ += distance;
}

void Player::move_left()
{
	const int distance = -32;
	pos_x_ += distance;
}

void Player::move_up()
{
	const int distance = -32;
	pos_y_ += distance;
}


void Player::move_down()
{
	const int distance = 32;
	pos_y_ += distance;
}

bool Player::is_above_water()
{
	return is_on_sth_;
}

void Player::set_is_above_water(bool n)
{
	is_on_sth_ = n;
}

void Player::lost()
{
	health_--;
	lose_frog();

	if(health_ < 1)
	{
		is_alive_ = false;
	}
}

bool Player::is_alive()
{
	return is_alive_;
}

int Player::health()
{
	return health_;
}

void Player::init()
{
	health_ = 3;
	is_on_sth_ = false;
	is_alive_ = true;
	has_frog_ = false;
}

void Player::attach_frog()
{
	has_frog_ = true;
}

void Player::lose_frog()
{
	has_frog_ = false;
}

bool Player::has_frog()
{
	return has_frog_;
}

void Player::reset_pos()
{
	pos_x_ = start_x_;
	pos_y_ = start_y_;
}



