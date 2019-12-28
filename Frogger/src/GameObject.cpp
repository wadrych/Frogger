#include "GameObject.h"

GameObject::GameObject(game_object* rect)
{
	sprite_ = TextureManager::load_texture(rect->path);

	pos_x_ = rect->x;
	pos_y_ = rect->y;

	src_r_.w = rect->w;
	src_r_.h = rect->h;
	src_r_.x = 0;
	src_r_.y = 0;
	dest_r_.w = rect->w;
	dest_r_.h = 32;

	velocity_ = rect->v;

	street_ = 2 * SCREEN_WIDTH;
}

GameObject::~GameObject()
{
}

void GameObject::render()
{
	SDL_RenderCopy(Global::renderer, sprite_, &src_r_, &dest_r_);
}

void GameObject::update()
{
	double distance = pos_x_ + velocity_;
	
	if (distance > street_)
	{
		distance = -(SCREEN_WIDTH / X_CHUNKS) * 6; // 6- cause log is max 6 tiles
	}
	else if (distance < -(SCREEN_WIDTH / X_CHUNKS) * 6)// 6- cause log is max 6 tiles
	{
		distance = street_;
	}

	pos_x_ = distance;
	
	dest_r_.x = (int)pos_x_;
	dest_r_.y = (int)pos_y_;
}

SDL_Texture* GameObject::get_texture()
{
	return sprite_;
}

void GameObject::set_x(double x)
{
	pos_x_ = x;
}

void GameObject::set_y(double y)
{
	pos_y_ = y;
}

SDL_Rect GameObject::get_dest_rect()
{
	return dest_r_;
}

double GameObject::get_x()
{
	return pos_x_;
}

double GameObject::get_y()
{
	return pos_y_;
}

SDL_Rect GameObject::get_src_rect()
{
	return src_r_;
}

void GameObject::set_velocity(int v)
{
	velocity_ = v;
}

double GameObject::get_velocity()
{
	return velocity_;
}

