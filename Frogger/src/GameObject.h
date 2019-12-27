#pragma once

#include "Global.h"
#include "TextureManager.h"

typedef struct game_object
{
	int x, y;
	int w, h;
	const char* path;
	double v;
} game_object;

class GameObject
{
public:
	GameObject(game_object* rect);
	~GameObject();

	void render();
	void update();
	void set_x(double x);
	void set_y(double y);

	double get_x();
	double get_y();
	
	SDL_Texture* get_texture();
	SDL_Rect get_dest_rect();
	SDL_Rect get_src_rect();
private:
	SDL_Texture* sprite;
	SDL_Rect src_r;
	SDL_Rect dest_r;

	double pos_x;
	double pos_y;
};
