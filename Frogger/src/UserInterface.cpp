#include "UserInterface.h"

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::init(const int surface_height, const int surface_width, const int window_height)
{
	this->surface_height_ = surface_height;
	this->surface_width_ = surface_width;
	
	dest_r_.w = surface_width;
	dest_r_.h = surface_height - 2;
	dest_r_.x = 0;
	dest_r_.y = window_height - surface_height;

	dest_r_bar_.w = surface_width / 4;
	dest_r_bar_.h = surface_height - 2;
	dest_r_bar_.x = 0;
	dest_r_bar_.y = window_height - surface_height;

	dest_r_menu_.w = surface_width - 40;
	dest_r_menu_.h = window_height - 100;
	dest_r_menu_.x = 20;
	dest_r_menu_.y = 50;
}


void  UserInterface::update_info(double world_time, double fps, int player_health, int score)
{	
	SDL_DestroyTexture(bar_text_);
	SDL_DestroyTexture(container_);
	
	char text[128];
	
	sprintf(text, "Health %2i Score %4i", player_health, score);
	draw_text_(&bar_text_, text);

	SDL_Surface* temp = create_time_bar(world_time);
	container_ = SDL_CreateTextureFromSurface(Global::renderer, temp);
	SDL_FreeSurface(temp);
	
}

SDL_Surface* UserInterface::create_time_bar(double world_time)
{
	const int health_bar_pixels = 200;
	const int game_time = 50;

	dest_r_.w = (int)(health_bar_pixels * (1 - (world_time / game_time)));

	//prevention against rect with 0 width
	if (dest_r_.w == 0)
	{
		dest_r_.w = 1;
	}

	dest_r_.x = SCREEN_WIDTH - dest_r_.w;

	SDL_Surface* temp = SDL_CreateRGBSurface(0, dest_r_.w, dest_r_.h, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	Uint32 outline = SDL_MapRGB(temp->format, 0x00, 0x00, 0x00);
	Uint32 fill = SDL_MapRGB(temp->format, 0xFF, 0xFF, 0x00);

	if (world_time >= 40 && world_time < 50)
	{
		fill = SDL_MapRGB(temp->format, 0xFF, 0x00, 0x00);
	}

	TextureManager::draw_rectangle(temp, 0, 0, dest_r_.w, dest_r_.h, outline, fill);

	return temp;
}

void UserInterface::render()
{

	SDL_RenderCopy(Global::renderer, container_, NULL, &dest_r_);
	SDL_RenderCopy(Global::renderer, bar_text_, NULL, &dest_r_bar_);
	SDL_RenderCopy(Global::renderer, menu_container_, NULL, &dest_r_menu_);
	SDL_RenderCopy(Global::renderer, menu_text_, NULL, &dest_r_text_);
	SDL_RenderCopy(Global::renderer, main_menu_container_, NULL, &menu_r_);
	SDL_RenderCopy(Global::renderer, game_name_, NULL, &game_name_r_);
	SDL_RenderCopy(Global::renderer, new_game_, NULL, &new_game_r_);
	SDL_RenderCopy(Global::renderer, new_game_text_, NULL, &new_game_t_r_);
	SDL_RenderCopy(Global::renderer, high_scores_, NULL, &high_scores_r_);
	SDL_RenderCopy(Global::renderer, high_scores_text_, NULL, &high_scores_t_r_);
	SDL_RenderCopy(Global::renderer, quit_, NULL, &quit_r_);
	SDL_RenderCopy(Global::renderer, quit_text_, NULL, &quit_t_r_);
}

void UserInterface::update_menu(option current)
{
	if (current == GAME_OVER)
	{
		dest_r_text_.w = dest_r_menu_.w - 200;
		dest_r_text_.h = 25;
		dest_r_text_.x = dest_r_menu_.x + 100;
		dest_r_text_.y = dest_r_menu_.y + 160;
		show_text("GAME OVER QUIT? Y/N");
	}
	else if (current == PAUSE)
	{
		dest_r_text_.w = dest_r_menu_.w - 300;
		dest_r_text_.h = 25;
		dest_r_text_.x = dest_r_menu_.x + 150;
		dest_r_text_.y = dest_r_menu_.y + 160;
		show_text("PAUSE");
	}
	else if (current == QUIT)
	{
		dest_r_text_.w = dest_r_menu_.w - 300;
		dest_r_text_.h = 25;
		dest_r_text_.x = dest_r_menu_.x + 150;
		dest_r_text_.y = dest_r_menu_.y + 160;
		show_text("QUIT GAME? Y/N");
	}
	else if (current == NEW_GAME || current == HIGH_SCORES || current == QUIT_GAME)
	{
		update_main_menu(current);
	}
}

void UserInterface::clean_menu()
{
	SDL_DestroyTexture(menu_text_);
	menu_text_ = NULL;
	SDL_DestroyTexture(menu_container_);
	menu_container_ = NULL;
	SDL_DestroyTexture(main_menu_container_);
	main_menu_container_ = NULL;
	SDL_DestroyTexture(game_name_);
	game_name_ = NULL;
	SDL_DestroyTexture(new_game_);
	new_game_ = NULL;
	SDL_DestroyTexture(new_game_text_);
	new_game_text_ = NULL;
	SDL_DestroyTexture(high_scores_);
	high_scores_ = NULL;
	SDL_DestroyTexture(high_scores_text_);
	high_scores_text_ = NULL;
	SDL_DestroyTexture(quit_);
	quit_ = NULL;
	SDL_DestroyTexture(quit_text_);
	quit_text_ = NULL;
}

void UserInterface::show_text(const char* text)
{
	clean_menu();

	draw_rect_(&menu_container_, dest_r_menu_, false);
	draw_text_(&menu_text_, text);
}

void UserInterface::update_main_menu(option current)
{
	menu_r_.w = SCREEN_WIDTH;
	menu_r_.h = SCREEN_HEIGHT;
	menu_r_.x = 0;
	menu_r_.y = 0;

	game_name_r_.w = 100;
	game_name_r_.h = 30;
	game_name_r_.x = SCREEN_WIDTH - 280;
	game_name_r_.y = 50;

	new_game_r_.w = 200;
	new_game_r_.h = game_name_r_.h;
	new_game_r_.x = game_name_r_.x - 50;
	new_game_r_.y = game_name_r_.y + game_name_r_.h + 30;

	new_game_t_r_.w = new_game_r_.w - 75;
	new_game_t_r_.h = new_game_r_.h - 10;
	new_game_t_r_.x = new_game_r_.x + 35;
	new_game_t_r_.y = new_game_r_.y + 5;

	high_scores_r_.w = 200;
	high_scores_r_.h = game_name_r_.h;
	high_scores_r_.x = game_name_r_.x - 50;
	high_scores_r_.y = new_game_r_.y + high_scores_r_.h + 30;

	high_scores_t_r_.w = high_scores_r_.w - 25;
	high_scores_t_r_.h = high_scores_r_.h - 10;
	high_scores_t_r_.x = high_scores_r_.x + 15;
	high_scores_t_r_.y = high_scores_r_.y + 5;
	
	quit_r_.w = 200;
	quit_r_.h = game_name_r_.h;
	quit_r_.x = game_name_r_.x - 50;
	quit_r_.y = high_scores_r_.y + quit_r_.h + 30;

	quit_t_r_.w = quit_r_.w - 140;
	quit_t_r_.h = quit_r_.h - 10;
	quit_t_r_.x = quit_r_.x + 70;
	quit_t_r_.y = quit_r_.y + 5;
	
	
	draw_rect_(&main_menu_container_, menu_r_, false);
	draw_text_(&game_name_, "FROGGER");

	draw_rect_(&new_game_, new_game_r_, current == NEW_GAME);
	draw_text_(&new_game_text_, "NEW GAME");

	draw_rect_(&high_scores_, high_scores_r_, current == HIGH_SCORES);
	draw_text_(&high_scores_text_, "HIGH SCORES");

	draw_rect_(&quit_, quit_r_, current == QUIT_GAME);
	draw_text_(&quit_text_, "QUIT");

}

void UserInterface::destroy()
{
	SDL_DestroyTexture(container_);
	SDL_DestroyTexture(menu_text_);
	SDL_DestroyTexture(bar_text_);
	SDL_DestroyTexture(menu_container_);
	SDL_DestroyTexture(main_menu_container_);
	SDL_DestroyTexture(game_name_);
	SDL_DestroyTexture(new_game_);
	SDL_DestroyTexture(new_game_text_);
	SDL_DestroyTexture(high_scores_);
	SDL_DestroyTexture(high_scores_text_);
	SDL_DestroyTexture(quit_);
	SDL_DestroyTexture(quit_text_);
	SDL_DestroyTexture(bonus_);
}

void UserInterface::draw_text_(SDL_Texture** texture, const char* text, bool wrap)
{
	SDL_DestroyTexture(*texture);
	
	char text_buffer[300];

	sprintf(text_buffer, text);
	SDL_Surface* text_surface;
	if(wrap)
	{
		text_surface = TTF_RenderText_Blended_Wrapped(Global::font, text, { 255,255,255 }, 700);//500
	}
	else
	{
		text_surface = TTF_RenderText_Solid(Global::font, text, { 255,255,255 });
	}

	if (text_surface == NULL)
	{
		printf("Unable to create TTF surface ! TTF Error: %s\n", TTF_GetError());
	}
	else
	{
		*texture = SDL_CreateTextureFromSurface(Global::renderer, text_surface);
		if (*texture == NULL)
		{
			printf("Unable to create menu texture ! SDL Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(text_surface);
	}
}

void UserInterface::draw_rect_(SDL_Texture** texture, SDL_Rect tex_r, bool current)
{
	SDL_DestroyTexture(*texture);
	
	SDL_Surface* temp_surface = SDL_CreateRGBSurface(0, tex_r.w, tex_r.h, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (temp_surface == NULL)
	{
		printf("Unable to create RGB surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		Uint32 line_color = SDL_MapRGB(temp_surface->format, 0x00, 0x00, 0xFF);
		if(current)
		{
			line_color = SDL_MapRGB(temp_surface->format, 0xFF, 0x00, 0x00);
		}
		const Uint32 container_color = SDL_MapRGB(temp_surface->format, 0x00, 0x00, 0x00);

		TextureManager::draw_rectangle(temp_surface, 0, 0, tex_r.w, tex_r.h, line_color, container_color);

		*texture = SDL_CreateTextureFromSurface(Global::renderer, temp_surface);
		if (*texture == NULL)
		{
			printf("Unable to create menu texture ! SDL Error: %s\n", SDL_GetError());
		}
	}
	SDL_FreeSurface(temp_surface);
}

void UserInterface::show_save_score(int score, char* name)
{
	dest_r_text_.w = dest_r_menu_.w - 50;
	dest_r_text_.h = 150;
	dest_r_text_.x = dest_r_menu_.x + 50;
	dest_r_text_.y = dest_r_menu_.y + 80;
	
	clean_menu();

	char text[128];
	sprintf(text, "Your score %i  Enter your name: %s", score, name);
	
	draw_rect_(&menu_container_, dest_r_menu_, false);
	draw_text_(&menu_text_, text, true);
}

void UserInterface::show_high_scores(result leaderboard[10], const int records_amt)
{
	clean_menu();
	
	new_game_t_r_.x = 30;
	new_game_t_r_.y = game_name_r_.y + 75;
	new_game_t_r_.w = 400;
	new_game_t_r_.h = 250;
	
	draw_rect_(&main_menu_container_, menu_r_, false);
	draw_text_(&game_name_, "HIGH SCORES");

	char text[300] = "";
	for(int i = 0; i < records_amt; i++)
	{
		char temp[30];
		sprintf(temp, "%2i. %8s - %5i  ", i + 1, leaderboard[i].name, leaderboard[i].score);
		
		strcat(text, temp);
	}
	
	draw_text_(&new_game_text_, text, true);
}

void UserInterface::show_bonus(SDL_Rect rect, int bonus)
{
	char buff[4] = "";
	sprintf(buff, "%i", bonus);
	
	draw_text_(&bonus_, buff);

	bonus_r_.w = 40;
	bonus_r_.h = 10;
	bonus_r_.x = rect.x;
	bonus_r_.y = rect.y - bonus_r_.h;


	SDL_RenderCopy(Global::renderer, bonus_, NULL, &bonus_r_);
	SDL_RenderPresent(Global::renderer);
	SDL_Delay(1000);
	SDL_DestroyTexture(bonus_);
	
}
