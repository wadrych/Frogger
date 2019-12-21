#pragma once

#include "Global.h"
#include "TextureManager.h"

class GameObject
{
public:
	GameObject(const char* path, int x, int y);
	~GameObject();

	void render();
	void update();
	void update_x(int x_distance);
	void update_y(int y_distance);

	int get_x();
	int get_y();
	
	SDL_Texture* get_texture();
	SDL_Rect get_dest_rect();
private:
	SDL_Texture* sprite;
	SDL_Rect src_r;
	SDL_Rect dest_r;

	int pos_x;
	int pos_y;
};