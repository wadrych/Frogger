#include "GameObject.h"

GameObject::GameObject(game_object* rect)
{
	sprite = TextureManager::load_texture(rect->path);

	pos_x = (int)rect->x;
	pos_y = (int)rect->y;

	src_r.w = rect->w;
	src_r.h = rect->h;
	src_r.x = 0;
	src_r.y = 0;
	dest_r.w = rect->w;
	dest_r.h = 32;
}

GameObject::~GameObject()
{
}

void GameObject::render()
{
	SDL_RenderCopy(Global::renderer, sprite, &src_r, &dest_r);
}

void GameObject::update()
{
	dest_r.x = (int)pos_x;
	dest_r.y = (int)pos_y;
}

SDL_Texture* GameObject::get_texture()
{
	return sprite;
}

void GameObject::set_x(double x)
{
	pos_x = x;
}

void GameObject::set_y(double y)
{
	pos_y = y;
}

SDL_Rect GameObject::get_dest_rect()
{
	return dest_r;
}

double GameObject::get_x()
{
	return pos_x;
}

double GameObject::get_y()
{
	return pos_y;
}

SDL_Rect GameObject::get_src_rect()
{
	return src_r;
}
