#pragma once

#include "Global.h"
#include "TextureManager.h"

class GameObject
{
public:
	GameObject(game_object* rect);
	~GameObject();

	void render();
	void update(double time = 0);
	void set_x(double x);
	void set_y(double y);

	double get_x();
	double get_y();
	
	SDL_Texture* get_texture();
	SDL_Rect get_dest_rect();
	SDL_Rect get_src_rect();
	void set_velocity(int v);
	double get_velocity();
	double get_delta();

protected:
	SDL_Texture* sprite_;
	SDL_Rect src_r_;
	SDL_Rect dest_r_;

	double pos_x_;
	double pos_y_;
	double start_x_;
	double start_y_;
	double velocity_;
	double delta_;
	int street_;
};
