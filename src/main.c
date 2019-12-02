/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:55:39 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/01 22:34:14 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double yaw(double a, double b, double c)
{
	return (a + b * c);
}

double v_c_p(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - x2 * y1);
}

t_coor	intersect(double x1, double y1, double x2, double y2,double x3, double y3,double x4, double y4)
{
	t_coor coor;
	double tmp1;
	double tmp2;
	double tmp3;
	double tmp4;

	tmp1 = v_c_p(x1, y1, x2, y2);
	tmp2 = x1 - x2;
	tmp3 = v_c_p(x3, y3, x4, y4);
	tmp4 = x3 - x4;
	coor.z = v_c_p(tmp1, tmp2, tmp3, tmp4);
	coor.x = (coor.z / v_c_p(x1 - x2, y1 - y2, x3 - x4, y3 - y4));
	tmp1 = v_c_p(x1, y1, x2, y2);
	tmp2 = y1 - y2;
	tmp3 = v_c_p(x3, y3, x4, y4);
	tmp4 = y3 - y4;
	coor.z = v_c_p(tmp1, tmp2, tmp3, tmp4);
	coor.y = (coor.z / v_c_p(x1 - x2, y1 - y2, x3 - x4, y3 - y4));
	coor.z = 0;
	return (coor);
}

static void draw_ceiling_floor(SDL_Renderer *ren, int x, int y1, int y2, int cya, int cyb, t_player p, Uint32 **textur)
{

	double	cy1;
	double	cy2;
	double	map_y;
	double	map_x;
	double	rot_x;
	double	rot_y;
	int		x_tex;
	int		y_tex;
	int		tmp;
	int		side;

    cy1 = (int)clamp(y1, 0, SIZE_Y-1);
    cy2 = (int)clamp(y2, 0, SIZE_Y-1);
    if(y2 >= y1)
    {
        while(cy1 <= cy2)
		{
			if (cy1 >= cya && cy1 <= cyb && cy1 != cy2)
			{
				cy1 = cyb;
				continue;
			}
			side = cy1 < cya ? 15 : 1;
			map_y = side * SIZE_Y * (vfov / (double)SIZE_Y) / ((SIZE_Y / 2 - cy1) - 0 * SIZE_Y * (vfov / (double)SIZE_Y));
			map_x = map_y * (SIZE_X / 2 - x) / (SIZE_X * hfov / (double)SIZE_X);
			rot_x = map_y * p.pcos + map_x * p.psin;
			rot_y = map_y * p.psin - map_x * p.pcos;
			map_x = rot_x + p.pos.x;
			map_y = rot_y + p.pos.y;
			if (map_x > 0)
				x_tex = (map_x * 128) / 6;
			else
				x_tex = 0;
			if (map_y > 0)
				y_tex = (map_y * 128) / 6;
			else
				y_tex = 0;
			tmp = (y_tex % 128) * 128 + (x_tex % 128);
			SDL_SetRenderDrawColor(ren, textur[0][tmp] >> 16 & 255, textur[0][tmp] >> 8 & 255, textur[0][tmp] >> 0 & 255, 0);
			SDL_RenderDrawPoint(ren, x, cy1);
			cy1++;
		}
    }
}

// void		special_line(int x)
// {
//
// }
//
// void		normal_line(int x, int y1, int y2, t_render *r)
// {
//
// 	int		wall_hei_from_bottom;
// 	double wall_hei_from_bottom = r->yb - y1;
// 	double 	wall_height_scale = (15 - 1) / 128;
// 	double wall_width_scale = 128 / 2 / r->wall_width;
// 	int start_x_tex;
// 	int	end_x_tex;
//
// 	if (vabs(r->t2.x - r->t1.x) > vabs(r->t2.z - r->t1.z))
// 	{
// 		start_x_tex = (r->t1.x - )
// 		end_x_tex =
// 	}
// 	else
// 	{
// 		start_x_tex =
// 		end_x_tex =
// 	}
// }
//
// void 		draw_wall_line(SDL_Renderer *ren, int x, int y1, int y2, int *ytop, t_render *r)
// {
// 	int y_tex_pos;
//
// 	y1 = clamp(y1, 0, SIZE_Y - 1);
// 	y2 = clamp(y2, 0, SIZE_Y - 1);
// 	if (y2 > y1)
// 	{
// 		if (clamp(ytop[x], 0, SIZE_Y - 1) == y1 && clamp(ytop[x], 0, SIZE_Y - 1))
// 		{
// 			special_line();
// 		}
// 		else
// 		{
// 			normal_line();
// 		}
// 	}
// }

static void vline(SDL_Renderer *ren, int x, int y1, int y2, int r, int v, int b)
{
	int y;

	SDL_SetRenderDrawColor(ren, r, v, b, 0);
    y1 = (int)clamp(y1, 0, SIZE_Y - 1);
    y2 = (int)clamp(y2, 0, SIZE_Y - 1);
    if(y2 >= y1)
    {
		y = y1;
        while(y <= y2)
		{
			SDL_RenderDrawPoint(ren, x, y);
			y++;
		}
    }
}

void init_wall_calcul(t_render *r, t_var *var, int nb_wall)
{
	double tmp1;
	double tmp2;

	r->v1.x = var->points[var->sectors[var->maps[0].sectors[0]].pts[0 + nb_wall]].x - var->player.pos.x;
	r->v1.y = var->points[var->sectors[var->maps[0].sectors[0]].pts[0 + nb_wall]].y - var->player.pos.y;
	r->v2.x = var->points[var->sectors[var->maps[0].sectors[0]].pts[1 + nb_wall]].x - var->player.pos.x;
	r->v2.y = var->points[var->sectors[var->maps[0].sectors[0]].pts[1 + nb_wall]].y - var->player.pos.y;
	tmp1 = var->points[var->sectors[var->maps[0].sectors[0]].pts[1 + nb_wall]].x - var->points[var->sectors[var->maps[0].sectors[0]].pts[0 + nb_wall]].x;
	tmp2 = var->points[var->sectors[var->maps[0].sectors[0]].pts[1 + nb_wall]].y - var->points[var->sectors[var->maps[0].sectors[0]].pts[0 + nb_wall]].y;
	r->wall_width = pythagore(tmp1, tmp2);
	r->t1.x = r->v1.x * var->player.psin - r->v1.y * var->player.pcos;
	r->t1.z = r->v1.x * var->player.pcos + r->v1.y * var->player.psin;
	r->t2.x = r->v2.x * var->player.psin - r->v2.y * var->player.pcos;
	r->t2.z = r->v2.x * var->player.pcos + r->v2.y * var->player.psin;
}

void check_wall_cut_by_the_window(t_render *r)
{
	r->i1 = intersect(r->t1.x, r->t1.z, r->t2.x, r->t2.z, -r->nearside,
		r->nearz, -r->farside, r->farz);
	r->i2 = intersect(r->t1.x, r->t1.z, r->t2.x, r->t2.z, r->nearside,
		r->nearz, r->farside, r->farz);
	if(r->t1.z < r->nearz)
	{
		if(r->i1.y > 0)
		{
			r->t1.x = r->i1.x;
			r->t1.z = r->i1.y;
		}
		else
		{
			r->t1.x = r->i2.x;
			r->t1.z = r->i2.y;
		}
	}
	if(r->t2.z < r->nearz)
	{
		if(r->i1.y > 0)
		{
			r->t2.x = r->i1.x;
			r->t2.z = r->i1.y;
		}
		else
		{
			r->t2.x = r->i2.x;
			r->t2.z = r->i2.y;
		}
	}
}

void calc_scaling(t_render *r)
{
	r->xscale1 = hfov / r->t1.z;
	r->yscale1 = vfov / r->t1.z;
	r->x1 = SIZE_X/2 - (int)(r->t1.x * r->xscale1);
	r->xscale2 = hfov / r->t2.z;
	r->yscale2 = vfov / r->t2.z;
	r->x2 = SIZE_X/2 - (int)(r->t2.x * r->xscale2);
}

void print_walls(t_render r, SDL_Renderer *render, int nb_wall, int *ytop, int *ybottom, t_var *var, Uint32 **wt)
{
	//int z;

	int beginx;
	int endx;

	beginx = max(r.x1, 0);
	endx = min(r.x2, SIZE_X - 1);
	for(int x = beginx; x <= endx; ++x)
	{
		//z = ((x - r.x1) * (r.t2.z - r.t1.z) / (r.x2 - r.x1) + r.t1.z) * 8;
		r.ya = (x - r.x1) * (r.y2a - r.y1a) / (r.x2 - r.x1) + r.y1a;
		r.cya = clamp(r.ya, ytop[x], ybottom[x]); // top
		r.yb = (x - r.x1) * (r.y2b - r.y1b) / (r.x2 - r.x1) + r.y1b;
		r.cyb = clamp(r.yb, ytop[x], ybottom[x]); // bottom
		draw_ceiling_floor(render, x, ytop[x], r.cya - 1, r.cya, r.cyb, var->player, wt);
		//draw_ceiling_floor(render, x, r.cyb + 1, SIZE_Y -1, r.cya, r.cyb, var->player, wt);
		vline(render, x, r.cyb + 1, SIZE_Y - 1, 150, 150, 150);

		//unsigned r = 0x010101 * (255 - z);
		if (nb_wall == 0)
			vline(render, x, r.cya, r.cyb, 255, 70, 20);
		else if (nb_wall == 1)
			vline(render, x, r.cya, r.cyb, 70, 255, 20);
		else if (nb_wall == 2)
			vline(render, x, r.cya, r.cyb, 100, 100, 20);
		else if (nb_wall == 3)
			vline(render, x, r.cya, r.cyb, 0, 150, 20);
		else if (nb_wall == 4)
			vline(render, x, r.cya, r.cyb, 30, 0, 20);
		else if (nb_wall == 5)
			vline(render, x, r.cya, r.cyb, 200, 150, 20);
		else if (nb_wall == 6)
			vline(render, x, r.cya, r.cyb, 66, 15, 20);
		else if (nb_wall == 7)
			vline(render, x, r.cya, r.cyb, 98, 7, 20);
		else
			vline(render, x, r.cya, r.cyb, 0, 0, 20);
	}
}

void init_nearz_farz(t_render *r)
{
	r->nearz = 1e-4f;
	r->farz = 5;
	r->nearside = 1e-5f;
	r->farside = 20.f;
}

void neo_display(t_var *var, SDL_Renderer *render, Uint32 **wt)
{
	double		pyaw;
	double		yceil;
	double		yfloor;
	int			ytop[SIZE_X]={0};
	int			ybottom[SIZE_X];
	t_render	r;
	int 		i;


	yceil = 15;
	yfloor = 1 - var->player.pos.z;
	pyaw = 0;
	init_nearz_farz(&r);
	i = 0;
	while (i < SIZE_X)
	{
		ybottom[i] = SIZE_Y - 1;
		i++;
	}
	for (unsigned nb_wall = 0; nb_wall != var->sectors[0].nb_pts - 1; nb_wall++)
	{
		init_wall_calcul(&r, var, nb_wall);
		if(r.t1.z <= 0 && r.t2.z <= 0)
			continue;
		if(r.t1.z <= 0 || r.t2.z <= 0)
			check_wall_cut_by_the_window(&r);
		calc_scaling(&r);
		if(r.x1 >= r.x2 || r.x2 < 0 || r.x1 > SIZE_X - 1)
			continue;
		r.y1a = SIZE_Y / 2 - (int)(yaw(yceil, r.t1.z, pyaw) * r.yscale1);
		r.y1b = SIZE_Y / 2 - (int)(yaw(yfloor, r.t1.z, pyaw) * r.yscale1);
        r.y2a = SIZE_Y / 2 - (int)(yaw(yceil, r.t2.z, pyaw) * r.yscale2);
		r.y2b = SIZE_Y / 2 - (int)(yaw(yfloor, r.t2.z, pyaw) * r.yscale2);
		print_walls(r, render, nb_wall, ytop, ybottom, var, wt);
	}
	SDL_RenderPresent(render);
}

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

	var->points[7].x = 0;
	var->points[7].y = 250;

	var->points[8].x = 100;
	var->points[8].y = 250;

	var->points[9].x = 150;
	var->points[9].y = 250;

	var->points[10].x = 250;
	var->points[10].y = 250;

	var->points[11].x = 250;
	var->points[11].y = 500;

	var->points[12].x = 0;
	var->points[12].y = 500;

	var->points[13].x = 0;
	var->points[13].y = 250;

	var->sectors = malloc(sizeof(t_sector) * 2);

	var->sectors[0].pts = malloc(sizeof(int) * 7);
	var->sectors[1].pts = malloc(sizeof(int) * 7);
 	var->sectors[0].nb_pts = 7;
	var->sectors[1].nb_pts = 7;

	var->sectors[0].pts[0] = 0;
	var->sectors[0].pts[1] = 1;
	var->sectors[0].pts[2] = 2;
	var->sectors[0].pts[3] = 3;
	var->sectors[0].pts[4] = 4;
	var->sectors[0].pts[5] = 5;
	var->sectors[0].pts[6] = 6;
	var->sectors[0].floor = 0;
	var->sectors[0].ceilling = 30;

	var->sectors[1].pts[0] = 7;
	var->sectors[1].pts[1] = 8;
	var->sectors[1].pts[2] = 9;
	var->sectors[1].pts[3] = 10;
	var->sectors[1].pts[4] = 11;
	var->sectors[1].pts[5] = 12;
	var->sectors[1].pts[6] = 13;
	var->sectors[1].floor = 0;
	var->sectors[1].ceilling = 30;

	var->maps[0].sectors = malloc(sizeof(int) * 2);

	var->maps[0].sectors[0] = 0;
	var->maps[0].sectors[1] = 1;
}

void init_player(t_var *var)
{
	var->player.pos.x = 50;
	var->player.pos.y = 50;
	var->player.pos.z = 10;
	var->player.angle = 0;
	var->player.pcos = cos(var->player.angle * RAD);
	var->player.psin = sin(var->player.angle * RAD);
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
	printf("%f\n", hfov);
	printf("%f\n", vfov);
}

void move_forward(t_var *var)
{
	double angle;

	angle = var->player.angle * RAD;
	// if (cos(angle) > 0)
	// {
	// 	var->player.pos.x = var->player.pos.x + cos(angle) * 10;
	// }
	// else
	if (cos(angle) != 0)
	{
		var->player.pos.x = var->player.pos.x + cos(angle) * 1;
	}
	// if (sin(angle) > 0)
	// {
	// 	var->player.pos.y = var->player.pos.y - sin(angle) * 10;
	// }
	// else
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y + sin(angle) * 1;
	}
//	var->player.pos.x = var->player.pos.x - cos((var->player.angle - (hfov / 2)) * RAD);
//	var->player.pos.y = var->player.pos.y - cos((var->player.angle - (hfov / 2)) * RAD);
}

void move_backward(t_var *var)
{
	double angle;

	angle = var->player.angle * RAD;
	if (cos(angle) != 0)
	{
		var->player.pos.x = var->player.pos.x - cos(angle) * 1;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y - sin(angle) * 1;
	}
}

void move_left(t_var *var)
{
	double angle;

	angle = (var->player.angle + 90) * RAD;
	if (cos(angle) != 0)
	{
		var->player.pos.x = var->player.pos.x - cos(angle) * 1;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y - sin(angle) * 1;
	}
}

void move_right(t_var *var)
{
	double angle;

	angle = (var->player.angle - 90) * RAD;
	if (cos(angle) != 0)
	{
		var->player.pos.x = var->player.pos.x - cos(angle) * 1;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y - sin(angle) * 1;
	}
}

SDL_Rect	create_sdl_rect(int x, int y, int w, int h)
{
	SDL_Rect r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return (r);
}

void	put_surface(SDL_Renderer *r, SDL_Surface *s, SDL_Rect dimensions)
{
	SDL_Texture	*mon_image;

	mon_image = SDL_CreateTextureFromSurface(r, s);
	SDL_QueryTexture(mon_image, NULL, NULL, &dimensions.w, &dimensions.h);
	SDL_SetRenderTarget(r, mon_image);
	SDL_RenderCopy(r, mon_image, NULL, &dimensions);
	SDL_DestroyTexture(mon_image);
}

void option()
{

}

void main_menu_g(SDL_Event ev, SDL_Surface *axe, SDL_Renderer *ren, int test_x, int test_y, SDL_Surface *main_menu, t_var *var)
{
	if (ev.type == SDL_MOUSEMOTION || ev.type == SDL_MOUSEBUTTONDOWN)
	{
		put_surface(ren, main_menu, create_sdl_rect(test_x,test_y,0,0));
		if (ev.motion.x > SIZE_X / 2 - 150 && ev.motion.x < SIZE_X / 2 + 150)
		{
			if (ev.motion.y > 350 && ev.motion.y < 500)
			{
				put_surface(ren, axe, create_sdl_rect(SIZE_X / 3 , 350, 0, 0));
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					var->kind_of_screen = SCREEN_ID_GAME;
				}
			}
		}
		SDL_RenderPresent(ren);
	}
}

void select_map()
{

}

void game(t_var *var, SDL_Event ev, SDL_Renderer *ren, Uint32 **walll_uint)
{
	if (var->key[MV_FORWARD] == ev.key.keysym.sym)
	{
		move_forward(var);
		neo_display(var,ren, walll_uint);
	}
	else if (var->key[MV_BACKWARD] == ev.key.keysym.sym)
	{
		move_backward(var);
		neo_display(var,ren, walll_uint);
	}
	else if (var->key[MV_LEFT] == ev.key.keysym.sym)
	{
		move_left(var);
		neo_display(var,ren, walll_uint);
	}
	else if (var->key[MV_RIGHT] == ev.key.keysym.sym)
	{
		move_right(var);
		neo_display(var,ren, walll_uint);
	}
	else if (ev.key.keysym.sym == SDLK_b)
	{
		edit_player_angle(var, -10);
		neo_display(var,ren, walll_uint);
	}
	else if (ev.key.keysym.sym == SDLK_m)
	{
		edit_player_angle(var, 10);
		neo_display(var,ren, walll_uint);
	}
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
	win = SDL_CreateWindow("DOOM NUKEM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SIZE_X, SIZE_Y, SDL_WINDOW_FULLSCREEN);
	ren = SDL_CreateRenderer(win, -1, 1);
	init_map(&var);
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
//	var.kind_of_screen = SCREEN_ID_GAME;

	//neo_display(&var,ren, walll_uint);
	int test_x = (1920 / 2 - SIZE_X / 2) * -1;
	int test_y = (1080 / 2 - SIZE_Y / 2 + 90) * -1;

	// int test_x = 0;
	// int test_y = -90;

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
