#include "Player.h"

Player::Player(const char* path, int x, int y) : GameObject(path, x, y)
{
	health = 10;
}

Player::~Player()
{
}

void Player::move_x(int distance)
{
	update_x(get_x() + distance);
}

void Player::move_y(int distance)
{
	update_y(get_y() + distance);
}

