#include "Player.h"

Player::Player(game_object* rect) : GameObject(rect)
{
	health = 10;
	is_on_sth = false;
}

Player::~Player()
{
}

void Player::move_right()
{
	int distance = SCREEN_WIDTH / X_CHUNKS;
	set_x(get_x() + distance);
}

void Player::move_left()
{
	int distance = SCREEN_WIDTH / X_CHUNKS;
	set_x(get_x() - distance);
}

void Player::move_up()
{
	int distance = (SCREEN_HEIGHT - GUI_HEIGHT) / Y_CHUNKS;
	set_y(get_y() - distance);
}


void Player::move_down()
{
	int distance = (SCREEN_HEIGHT - GUI_HEIGHT) / Y_CHUNKS;
	set_y(get_y() + distance);
}

bool Player::is_above_water()
{
	return is_on_sth;
}

void Player::set_is_above_water(bool n)
{
	is_on_sth = n;
}

