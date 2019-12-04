/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:01:35 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/04 16:06:21 by vgauther         ###   ########.fr       */
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

void init_wall_calcul(t_render *r, t_var *var, int nb_wall, int s)
{
	double tmp1;
	double tmp2;

	r->v1.x = var->points[var->sectors[var->maps[0].sectors[s]].pts[0 + nb_wall]].x - var->player.pos.x;
	r->v1.y = var->points[var->sectors[var->maps[0].sectors[s]].pts[0 + nb_wall]].y - var->player.pos.y;
	r->v2.x = var->points[var->sectors[var->maps[0].sectors[s]].pts[1 + nb_wall]].x - var->player.pos.x;
	r->v2.y = var->points[var->sectors[var->maps[0].sectors[s]].pts[1 + nb_wall]].y - var->player.pos.y;
	tmp1 = var->points[var->sectors[var->maps[0].sectors[s]].pts[1 + nb_wall]].x - var->points[var->sectors[var->maps[0].sectors[s]].pts[0 + nb_wall]].x;
	tmp2 = var->points[var->sectors[var->maps[0].sectors[s]].pts[1 + nb_wall]].y - var->points[var->sectors[var->maps[0].sectors[s]].pts[0 + nb_wall]].y;
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

void print_walls(t_render r, SDL_Renderer *render, int nb_wall, int *ytop, int *ybottom, t_var *var, Uint32 **wt, int nei)
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
		if (nei >= 0)
		{
			int nya = (x - r.x1) * (r.ny2a-r.ny1a) / (r.x2-r.x1) + r.ny1a, cnya = clamp(nya, ytop[x],ybottom[x]);
            int nyb = (x - r.x1) * (r.ny2b-r.ny1b) / (r.x2-r.x1) + r.ny1b, cnyb = clamp(nyb, ytop[x],ybottom[x]);
			vline(render, x, r.cya, cnya-1, 0, 255, 0); // Between our and their ceiling
			ytop[x] = clamp(max(r.cya, cnya), ytop[x], SIZE_Y - 1);
			vline(render, x, cnyb+1, r.cyb, 0, 255, 0); // Between their and our floor
			ybottom[x] = clamp(min(r.cyb, cnyb), 0, ybottom[x]);
		//unsigned r = 0x010101 * (255 - z);
		}
		else
		{
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
}

void init_nearz_farz(t_render *r, t_reader *read)
{
	read->head = read->queue;
	read->tail = read->queue;
	read->head->sectorno = 0;
	read->head->sx1 = 0;
	read->head->sx2 = SIZE_X - 1;
	if (++read->head == read->queue + 32)
		read->head = read->queue;
	r->nearz = 1e-4f;
	r->farz = 5;
	r->nearside = 1e-5f;
	r->farside = 20.f;
}

int		init_queue(t_reader *read, int *renderedsectors)
{
	read->now = *read->tail;
	if (++read->tail == read->queue + 32)
		read->tail = read->queue;
	if (renderedsectors[read->now.sectorno] & (32 + 1))
		return (-1);
	return (0);
}

void neo_display(t_var *var, SDL_Renderer *render, Uint32 **wt)
{
	double		pyaw;
	double		yceil;
	double		yfloor;
	int			ytop[SIZE_X];
	int			ybottom[SIZE_X];
	t_render	r;
	int 		i;
	t_reader	read;
	int nosector;
	int network;
	int nyfloor;
	int nyceil;
	int			renderedsectors[2];
	int x = 0;
	yceil = 15;
	yfloor = 1 - var->player.pos.z;
	pyaw = 0;

	while (++x < 2)
		renderedsectors[x] = 0;
	init_nearz_farz(&r, &read);
	i = 0;
	while (i < SIZE_X)
	{
		ybottom[i] = SIZE_Y - 1;
		ytop[i] = 0;
		i++;
	}
	while (read.tail != read.head)
	{
		if (init_queue(&read, renderedsectors) == -1)
			continue;
		++renderedsectors[read.now.sectorno];
		nosector = read.now.sectorno;
		for (unsigned nb_wall = 0; nb_wall != var->sectors[read.now.sectorno].nb_pts - 1; nb_wall++)
		{
			init_wall_calcul(&r, var, nb_wall, read.now.sectorno);
			if(r.t1.z <= 0 && r.t2.z <= 0)
				continue;
			if(r.t1.z <= 0 || r.t2.z <= 0)
				check_wall_cut_by_the_window(&r);
			calc_scaling(&r);
			if(r.x1 >= r.x2 || r.x2 < 0 || r.x1 > SIZE_X - 1)
				continue;
			network = var->sectors[read.now.sectorno].neighbors[nb_wall];
			nyceil = 0;
			nyfloor = 0;
			if (network >= 0)
			{
				nyceil = 15;
				nyfloor = 1 - var->player.pos.z;

			}
			r.y1a = SIZE_Y / 2 - (int)(yaw(yceil, r.t1.z, pyaw) * r.yscale1);
			r.y1b = SIZE_Y / 2 - (int)(yaw(yfloor, r.t1.z, pyaw) * r.yscale1);
        	r.y2a = SIZE_Y / 2 - (int)(yaw(yceil, r.t2.z, pyaw) * r.yscale2);
			r.y2b = SIZE_Y / 2 - (int)(yaw(yfloor, r.t2.z, pyaw) * r.yscale2);
			r.ny1a = SIZE_Y / 2 - (int)(yaw(nyceil, r.t1.z, pyaw) * r.yscale1);
			r.ny1b = SIZE_Y / 2 - (int)(yaw(nyfloor, r.t1.z, pyaw) * r.yscale1);
			r.ny2a = SIZE_Y / 2 - (int)(yaw(nyceil, r.t2.z, pyaw) * r.yscale2);
			r.ny2b = SIZE_Y / 2 - (int)(yaw(nyfloor, r.t2.z, pyaw) * r.yscale2);
			print_walls(r, render, nb_wall, ytop, ybottom, var, wt, network);
		}
		++renderedsectors[read.now.sectorno];
	}
	SDL_RenderPresent(render);
}
