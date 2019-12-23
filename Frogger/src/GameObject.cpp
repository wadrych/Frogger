#include "GameObject.h"

GameObject::GameObject(game_object* rect)
{
	sprite = TextureManager::load_texture(rect->path);

	pos_x = rect->x;
	pos_y = rect->y;

	src_r.w = rect->w;
	src_r.h = rect->h;
	src_r.x = 0;
	src_r.y = 0;
	dest_r.w = rect->w / (SCREEN_WIDTH / X_CHUNKS) * (SCREEN_WIDTH / X_CHUNKS);
	dest_r.h = (SCREEN_HEIGHT - GUI_HEIGHT) / Y_CHUNKS;
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
	dest_r.x = pos_x;
	dest_r.y = pos_y;
}

SDL_Texture* GameObject::get_texture()
{
	return sprite;
}

void GameObject::set_x(int x)
{
	pos_x = x;
}

void GameObject::set_y(int y)
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
