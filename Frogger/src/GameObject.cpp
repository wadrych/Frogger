#include "GameObject.h"

GameObject::GameObject(const char* path, int x, int y)
{
	sprite = TextureManager::load_texture(path);

	pos_x = x;
	pos_y = y;
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
	src_r.w = 32;
	src_r.h = 32;
	src_r.x = 0;
	src_r.y = 0;

	dest_r.w = 32;
	dest_r.h = 32;
	dest_r.x = pos_x;
	dest_r.y = pos_y;
}

SDL_Texture* GameObject::get_texture()
{
	return sprite;
}

void GameObject::update_x(int x)
{
	pos_x = x;
}

void GameObject::update_y(int y)
{
	pos_y = y;
}

SDL_Rect GameObject::get_dest_rect()
{
	return dest_r;
}

int GameObject::get_x()
{
	return pos_x;
}

int GameObject::get_y()
{
	return pos_y;
}
