#pragma once

#include "Global.h"
#include "TextureManager.h"

typedef struct game_object
{
	int x, y;
	int w, h;
	const char* path;
	int v;
} game_object;

class GameObject
{
public:
	GameObject(game_object* rect);
	~GameObject();

	void render();
	void update();
	void set_x(int x);
	void set_y(int y);

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
