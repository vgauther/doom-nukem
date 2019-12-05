/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:55:39 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/05 16:48:53 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void init_map(t_var *var)
{
	var->maps = malloc(sizeof(t_map) * 1);

	var->points = malloc(sizeof(t_point) * 14);

	var->points[0].x = 0;
	var->points[0].y = 0;

	var->points[1].x = 250;
	var->points[1].y = 0;

	var->points[2].x = 250;
	var->points[2].y = 250;

	var->points[3].x = 150;
	var->points[3].y = 250;

	var->points[4].x = 100;
	var->points[4].y = 250;

	var->points[5].x = 0;
	var->points[5].y = 250;

	var->points[6].x = 0;
	var->points[6].y = 0;

	var->points[7].x = 150;
	var->points[7].y = 250;

	var->points[8].x = 150;
	var->points[8].y = 350;

	var->points[9].x = 100;
	var->points[9].y = 350;

	var->points[10].x = 100;
	var->points[10].y = 250;

	var->points[11].x = 150;
	var->points[11].y = 250;

	var->sectors = malloc(sizeof(t_sector) * 2);

	var->sectors[0].pts = malloc(sizeof(int) * 7);
	var->sectors[1].pts = malloc(sizeof(int) * 5);

	var->sectors[0].neighbors = malloc(sizeof(int) * 7);
	var->sectors[1].neighbors = malloc(sizeof(int) * 5);

 	var->sectors[0].nb_pts = 7;
	var->sectors[1].nb_pts = 5;

	var->sectors[0].pts[0] = 0;
	var->sectors[0].pts[1] = 1;
	var->sectors[0].pts[2] = 2;
	var->sectors[0].pts[3] = 3;
	var->sectors[0].pts[4] = 4;
	var->sectors[0].pts[5] = 5;
	var->sectors[0].pts[6] = 6;

	var->sectors[0].floor = 0;
	var->sectors[0].ceilling = 30;

	var->sectors[0].neighbors[0] = -1;
	var->sectors[0].neighbors[1] = -1;
	var->sectors[0].neighbors[2] = -1;
	var->sectors[0].neighbors[3] = 1;
	var->sectors[0].neighbors[4] = -1;
	var->sectors[0].neighbors[5] = -1;
	var->sectors[0].neighbors[6] = -1;

	var->sectors[1].pts[0] = 7;
	var->sectors[1].pts[1] = 8;
	var->sectors[1].pts[2] = 9;
	var->sectors[1].pts[3] = 10;
	var->sectors[1].pts[4] = 11;

	var->sectors[1].floor = 5;
	var->sectors[1].ceilling = 25;

	var->sectors[1].neighbors[0] = -1;
	var->sectors[1].neighbors[1] = -1;
	var->sectors[1].neighbors[2] = -1;
	var->sectors[1].neighbors[3] = -1;
	var->sectors[1].neighbors[4] = 0;

	var->maps[0].sectors = malloc(sizeof(int) * 2);

	var->maps[0].sectors[0] = 0;
	var->maps[0].sectors[1] = 1;
}

void init_player(t_var *var)
{
	var->player.pos.x = 150;
	var->player.pos.y = 150;
	var->player.pos.z = 10;
	var->player.angle = 90;
	var->player.yaw = 0;
	var->player.pcos = cos(var->player.angle * RAD);
	var->player.psin = sin(var->player.angle * RAD);
	var->player.sector = 0;
}

void	edit_player_angle(t_var *var, int x)
{
	var->player.angle += x;
	var->player.pcos = cos(var->player.angle * RAD);
	var->player.psin = sin(var->player.angle * RAD);
}

void edit_key(t_var *var, int key_to_change, int new_key)
{
	var->key[key_to_change] = new_key;
}

void init_key(t_var *var)
{
	var->key[MV_FORWARD] = SDLK_w;
	var->key[MV_BACKWARD] = SDLK_s;
	var->key[MV_LEFT] = SDLK_a;
	var->key[MV_RIGHT] = SDLK_d;
}

void option(SDL_Renderer *ren)
{
	int test_x = (2560 / 2 - SIZE_X / 2) * -1;
	int test_y = (1440 / 2 - SIZE_Y / 2) * -1;
	SDL_Surface *s;

	s = SDL_LoadBMP("./opt.bmp");

	put_surface(ren, s, create_sdl_rect(test_x, test_y, 0, 0));
}

void select_map(SDL_Renderer *ren)
{
	int test_x = (2560 / 2 - SIZE_X / 2) * -1;
	int test_y = (1440 / 2 - SIZE_Y / 2) * -1;
	SDL_Surface *s;

	s = SDL_LoadBMP("./sm.bmp");

	put_surface(ren, s, create_sdl_rect(test_x, test_y, 0, 0));
	//put_surface(ren, main_menu, create_sdl_rect(test_x,test_y,0,0));
}

void main_menu_g(SDL_Event ev, SDL_Surface *axe, SDL_Renderer *ren, int test_x, int test_y, SDL_Surface *main_menu, t_var *var)
{
	if (ev.type == SDL_MOUSEMOTION || ev.type == SDL_MOUSEBUTTONDOWN)
	{
		put_surface(ren, main_menu, create_sdl_rect(test_x,test_y,0,0));
		if (ev.motion.x > SIZE_X / 2 - 210 && ev.motion.x < SIZE_X / 2 + 200)
		{
			if (ev.motion.y > SIZE_Y / 2 - 140 && ev.motion.y < SIZE_Y / 2 - 20)
			{
				put_surface(ren, axe, create_sdl_rect(SIZE_X / 2 - (axe->w / 2) - 210, SIZE_Y / 2 - (axe->h / 2) - 85, 0, 0));
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					var->kind_of_screen = SCREEN_ID_GAME;
				}
			}
			else if (ev.motion.y > SIZE_Y / 2 - 80 && ev.motion.y < SIZE_Y / 2 + 80)
			{
				put_surface(ren, axe, create_sdl_rect(SIZE_X / 2 - (axe->w / 2) - 210, SIZE_Y / 2 - 20, 0, 0));
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					var->kind_of_screen = SCREEN_ID_SELECTMAP;
					select_map(ren);
				}
			}
			else if (ev.motion.y > SIZE_Y / 2 - 60 && ev.motion.y < SIZE_Y / 2 + 180)
			{
				put_surface(ren, axe, create_sdl_rect(SIZE_X / 2 - (axe->w / 2) - 300, SIZE_Y / 2 + 80, 0, 0));
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					var->kind_of_screen = SCREEN_ID_OPTION;
					option(ren);
				}
			}
			else if (ev.motion.y > SIZE_Y / 2 + 80 && ev.motion.y < SIZE_Y / 2 + 280)
			{
				put_surface(ren, axe, create_sdl_rect(SIZE_X / 2 - (axe->w / 2) - 210, SIZE_Y / 2 + 180, 0, 0));
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					SDL_Quit();
					exit(0);
				}
			}
		}
		SDL_RenderPresent(ren);
	}
}

void game(t_var *var, SDL_Event ev, SDL_Renderer *ren, Uint32 **walll_uint)
{
	if (var->key[MV_FORWARD] == ev.key.keysym.sym)
	{
		move_forward(var);
		DrawScreen(var, ren, walll_uint);
		(void)walll_uint;
	}
	else if (var->key[MV_BACKWARD] == ev.key.keysym.sym)
	{
		move_backward(var);
		DrawScreen(var, ren, walll_uint);
	}
	else if (var->key[MV_LEFT] == ev.key.keysym.sym)
	{
		move_left(var);
		DrawScreen(var, ren, walll_uint);
	}
	else if (var->key[MV_RIGHT] == ev.key.keysym.sym)
	{
		move_right(var);
		DrawScreen(var, ren, walll_uint);
	}
	else if (ev.key.keysym.sym == SDLK_b)
	{
		edit_player_angle(var, -10);
		DrawScreen(var, ren, walll_uint);
	}
	else if (ev.key.keysym.sym == SDLK_m)
	{
		edit_player_angle(var, 10);
		DrawScreen(var, ren, walll_uint);
	}
}

void init_farz_nearz(t_var *v)
{
	v->nearz = 1e-4f;
	v->farz = 5;
	v->nearside = 1e-5f;
	v->farside = 20.f;
}

int				main(int ac, char **av)
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		ev;
	t_var			var;
	SDL_Surface		*wall[4];
	Uint32			*walll_uint[4];
	SDL_Surface		*main_menu;
	SDL_Surface		*axe;

	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("DOOM NUKEM", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SIZE_X, SIZE_Y, SDL_WINDOW_OPENGL);
	ren = SDL_CreateRenderer(win, -1, 1);
	init_map(&var);
	init_farz_nearz(&var);
	wall[0] = SDL_LoadBMP("./assets/t1.bmp");
	wall[1] = SDL_LoadBMP("./assets/t2.bmp");
	wall[2] = SDL_LoadBMP("./assets/t3.bmp");
	wall[3] = SDL_LoadBMP("./assets/t4.bmp");
	walll_uint[0] = (Uint32 *)wall[0]->pixels;
	walll_uint[1] = (Uint32 *)wall[1]->pixels;
	walll_uint[2] = (Uint32 *)wall[2]->pixels;
	walll_uint[3] = (Uint32 *)wall[3]->pixels;
	axe = SDL_LoadBMP("axe.bmp");
	main_menu = SDL_LoadBMP("./menu.bmp");
	init_player(&var);
	init_key(&var);
	var.kind_of_screen = SCREEN_ID_MENU;
	var.number_of_sector = 2;

	int test_x = (2560 / 2 - SIZE_X / 2) * -1;
	int test_y = (1440 / 2 - SIZE_Y / 2) * -1;

	put_surface(ren, main_menu, create_sdl_rect(test_x,test_y,0,0));
	SDL_RenderPresent(ren);
	while (SDL_WaitEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
			break ;
		else if (ev.key.keysym.sym == SDLK_ESCAPE)
			break ;
		else if (ev.type == SDL_KEYDOWN)
		{
			if (var.kind_of_screen == SCREEN_ID_GAME)
				game(&var, ev, ren, walll_uint);
		}
		else if (var.kind_of_screen == SCREEN_ID_MENU)
		{
			main_menu_g(ev, axe, ren, test_x, test_y, main_menu, &var);
		}
		// else if (var.kind_of_screen = SCREEN_ID_SELECTMAP)
		// {
		// 	select_map();
		// }
		// else if (var.kind_of_screen = SCREEN_ID_OPTION)
		// {
		// 	option();
		// }
	}
	SDL_Quit();
	exit(0);
	(void)ac;
	(void)av;
	return (0);
}
