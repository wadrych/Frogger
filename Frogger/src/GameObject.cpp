#include "GameObject.h"

GameObject::GameObject(game_object* rect)
{
	sprite_ = TextureManager::load_texture(rect->path);

	pos_x_ = rect->x;
	pos_y_ = rect->y;
	start_x_ = pos_x_;
	start_y_ = pos_y_;

	src_r_.w = rect->w;
	src_r_.h = rect->h;
	src_r_.x = 0;
	src_r_.y = 0;
	dest_r_.w = rect->w;
	dest_r_.h = 32; //height of one chunk

	velocity_ = rect->v;

	street_ = 2 * SCREEN_WIDTH; //so the objects would travel distance of two screens
}

GameObject::~GameObject()
{
}

void GameObject::render()
{
	SDL_RenderCopy(Global::renderer, sprite_, &src_r_, &dest_r_);
}

void GameObject::update(double time)
{
	double distance_ = (int)(time * velocity_*50 + start_x_) % street_ - (SCREEN_WIDTH / X_CHUNKS) * 6;
	if (velocity_ < 0)
	{
		distance_ = street_ + ((int)(time * velocity_ * 50 - start_x_) % street_) - (SCREEN_WIDTH / X_CHUNKS) * 6;
	}

	delta_ = fabs(pos_x_ - distance_);

	if(velocity_ != 0)
	{
		pos_x_ = distance_;
	}
	
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

double GameObject::get_delta()
{
	return delta_;
}

