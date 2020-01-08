/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:55:39 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/15 17:14:34 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void init_map(t_var *var)
{
	var->maps = malloc(sizeof(t_map) * 2);
	var->m_count = 2;

	var->points = malloc(sizeof(t_point) * 12);

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

	var->sectors[0].neighbors = malloc(sizeof(int) * 6);
	var->sectors[1].neighbors = malloc(sizeof(int) * 4);

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

	var->sectors[1].pts[0] = 7;
	var->sectors[1].pts[1] = 8;
	var->sectors[1].pts[2] = 9;
	var->sectors[1].pts[3] = 10;
	var->sectors[1].pts[4] = 11;

	var->sectors[1].floor = 2;
	var->sectors[1].ceilling = 30;

	var->sectors[1].neighbors[0] = -1;
	var->sectors[1].neighbors[1] = -1;
	var->sectors[1].neighbors[2] = -1;
	var->sectors[1].neighbors[3] = 0;

	var->maps[0].sectors = malloc(sizeof(int) * 2);

	var->maps[1].sectors = malloc(sizeof(int) * 1);

	var->maps[0].spawn_x = 240;
	var->maps[0].spawn_y = 240;

	var->maps[0].end_lv_x = 0;
	var->maps[0].end_lv_y = 0;

	var->maps[1].spawn_x = 50;
	var->maps[1].spawn_y = 50;

	var->maps[1].end_lv_x = 240;
	var->maps[1].end_lv_y = 240;

	var->maps[0].sectors[0] = 0;
	var->maps[0].sectors[1] = 1;

	var->maps[1].sectors[0] = 0;
	var->maps[1].sectors[1] = 1;

}

void init_player(t_var *var)
{
	var->player.pos.x = 240;
	var->player.pos.y = 240;
	var->player.pos.z = 10;
	var->player.angle = 90;
	var->player.yaw = 0;
	var->player.pcos = cos(var->player.angle * RAD);
	var->player.psin = sin(var->player.angle * RAD);
	var->player.map = 0;
	var->player.sector = var->maps[var->player.map].sectors[0];
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
	var->key[MV_FORWARD] = SDL_SCANCODE_W;
	var->key[MV_BACKWARD] = SDL_SCANCODE_S;
	var->key[MV_LEFT] = SDL_SCANCODE_A;
	var->key[MV_RIGHT] = SDL_SCANCODE_D;
}

void option(SDL_Renderer *ren)
{
	int test_x = (2560 / 2 - SIZE_X / 2) * -1;
	int test_y = (1440 / 2 - SIZE_Y / 2) * -1;
	SDL_Surface *s;
	SDL_Surface *s1;
	SDL_Rect r = create_sdl_rect(0, 0, 0,0);

	s = SDL_LoadBMP("./assets/opt.bmp");
	s1 = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
	//SDL_FillRect(s1, &r, 10000000);
	Uint32 *tmp = (Uint32*)s1->pixels;
	int z;

	z = 0;
	while (z < 50 * 50 - 50)
	{
		tmp[z] = (200 << 24) + (0 << 16) + (0 << 8) + (255 << 0 );
		z++;
		ft_putstr("m\n");
	}
	s1->pixels = (void *)tmp;

	put_surface(ren, s1, r);
	put_surface(ren, s, create_sdl_rect(test_x, test_y, 0, 0));
}

void select_map(SDL_Renderer *ren, SDL_Event ev)
{
	int test_x = (2560 / 2 - SIZE_X / 2) * -1;
	int test_y = (1440 / 2 - SIZE_Y / 2) * -1;
	SDL_Surface *s;

	s = SDL_LoadBMP("./assets/sm.bmp");
	put_surface(ren, s, create_sdl_rect(test_x, test_y, 0, 0));
	SDL_FreeSurface(s);
	SDL_RenderPresent(ren);
	(void)ev;
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
					select_map(ren, ev);
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

void game(t_var *var, SDL_Event ev, SDL_Renderer *ren, Uint32 **walll_uint, const Uint8 *inkeys)
{
	if (inkeys[var->key[MV_FORWARD]])
	{
		if (!inkeys[SDL_SCANCODE_LSHIFT])
			move_forward(var, 0.50);
		else
			move_forward(var, 1.20);
		DrawScreen(var, ren, walll_uint);
		(void)walll_uint;
	}
	if (inkeys[var->key[MV_BACKWARD]])
	{
		move_backward(var);
		DrawScreen(var, ren, walll_uint);
	}
	if (inkeys[var->key[MV_LEFT]])
	{
		move_left(var);
		DrawScreen(var, ren, walll_uint);
	}
	if (inkeys[var->key[MV_RIGHT]])
	{
		move_right(var);
		DrawScreen(var, ren, walll_uint);
	}
	if (ev.key.keysym.sym == SDLK_b)
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

void sdl_quit_exit(void)
{
	SDL_Quit();
	exit(0);
}

int		ren_create_fail(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (-1);
}

int		open_audio_fail(SDL_Window *win, SDL_Renderer *ren)
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
	return (-1);
}

int				main(int ac, char **av)
{

	t_var			var;
	Uint32			*walll_uint[4];
	int				stop;

	stop = 1;
	// bzero(&ev, sizeof(SDL_Event));
	// bzero(&win, sizeof(SDL_Window *));
	// bzero(&ren, sizeof(SDL_Renderer *));
	// bzero(&var, sizeof(t_var));


	// SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	// win = SDL_CreateWindow("DOOM NUKEM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, SDL_WINDOW_OPENGL);
	// ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	var.kind_of_screen = SCREEN_ID_MENU;
	var.number_of_sector = 2;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		ft_putstr("error init video");
		return (-1);
	}
	ft_putstr("SDL_INITED\n");
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*main_menu;
	SDL_Surface		*axe;
	Mix_Music 		*musique;
	SDL_Event		eve;

	win = SDL_CreateWindow("DOOM NUKEM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, SDL_WINDOW_SHOWN);
	if (!(ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)))
		return (ren_create_fail(win));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (open_audio_fail(win, ren));
	SDL_Surface		*wall[4];
	musique = Mix_LoadMUS("./music/mu.wav");
	Mix_PlayMusic(musique, -1);
	//fill_data_struct(&var);
	init_map(&var);

	init_key(&var);
	init_player(&var);
	init_farz_nearz(&var);
	wall[0] = SDL_LoadBMP("./assets/t1.bmp");
	wall[1] = SDL_LoadBMP("./assets/t2.bmp");
	wall[2] = SDL_LoadBMP("./assets/t3.bmp");
	wall[3] = SDL_LoadBMP("./assets/t4.bmp");
	walll_uint[0] = (Uint32 *)wall[0]->pixels;
	walll_uint[1] = (Uint32 *)wall[1]->pixels;
	walll_uint[2] = (Uint32 *)wall[2]->pixels;
	walll_uint[3] = (Uint32 *)wall[3]->pixels;
	axe = SDL_LoadBMP("./assets/axe.bmp");
	main_menu = SDL_LoadBMP("./assets/menu.bmp");
	int test_x = (2560 / 2 - SIZE_X / 2) * -1;
	int test_y = (1440 / 2 - SIZE_Y / 2) * -1;

	const Uint8			*inkeys;
	while(stop)
	{
		inkeys = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&eve))
		{
			if (eve.type == SDL_QUIT)
			{
				stop = 0;
				break ;
			}
			else if (eve.key.keysym.sym == SDLK_ESCAPE)
			{
				stop = 0;
				break ;
			}
			if (var.kind_of_screen == SCREEN_ID_GAME)
			{
				if (eve.type == SDL_KEYDOWN)
					game(&var, eve, ren, walll_uint, inkeys);
			}
			else if (var.kind_of_screen == SCREEN_ID_MENU)
			{
				main_menu_g(eve, axe, ren, test_x, test_y, main_menu, &var);
			}
			else if (var.kind_of_screen == SCREEN_ID_SELECTMAP)
			{
				select_map(ren, eve);
			}
			else if (var.kind_of_screen == SCREEN_ID_OPTION)
			{
				option(ren);
			}
		}
	}
	walll_uint[0] = NULL;
	walll_uint[1] = NULL;
	walll_uint[2] = NULL;
	walll_uint[3] = NULL;
	Mix_FreeMusic(musique);
	SDL_FreeSurface(axe);
	SDL_FreeSurface(main_menu);
	SDL_FreeSurface(wall[0]);
	SDL_FreeSurface(wall[1]);
	SDL_FreeSurface(wall[2]);
	SDL_FreeSurface(wall[3]);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	Mix_CloseAudio();
	SDL_Quit();
	exit(0);
	(void)ac;
	(void)av;
	return (0);
}
