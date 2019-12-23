#include "Player.h"

Player::Player(game_object* rect) : GameObject(rect)
{
	health = 10;
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

