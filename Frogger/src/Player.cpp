#include "Player.h"

Player::Player(game_object* rect) : GameObject(rect)
{
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
}
