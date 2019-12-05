/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:01:35 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/05 14:31:11 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double yaw(double a, double b, double c)
{
	return (a + b * c);
}

static void draw_ceiling(SDL_Renderer *ren, int x, int y1, int y2, int cya, int cyb, t_player p, Uint32 **textur, int floor, int ceil)
{

	double cy1;
	double cy2;
	int side;
	double map_y;
	double map_x;
	double rot_x;
	double rot_y;
	int x_tex;
	int y_tex;
	int tmp;

    cy1 = (int)clamp(y1, 0, SIZE_Y - 1);
    cy2 = (int)clamp(y2, 0, SIZE_Y - 1);
    if(y2 >= y1)
    {
        while(cy1 <= cy2)
		{
			if (cy1 >= cya && cy1 <= cyb && cy1 != cy2)
			{
				cy1 = cyb;
				continue;
			}
			side = cy1 < cya ? ceil : floor;
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
			SDL_SetRenderDrawColor(ren, textur[1][tmp] >> 16 & 255, textur[1][tmp] >> 8 & 255, textur[1][tmp] >> 0 & 255, 0);
			SDL_RenderDrawPoint(ren, x, cy1);
			cy1++;
		}
    }
}

double v_c_p(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - x2 * y1);
}

static void vline(SDL_Renderer *ren, int x, int y1,int y2, int top,int middle,int bottom)
{
	int y;

	SDL_SetRenderDrawColor(ren, middle >> 16 & 255, middle >> 8 & 255, middle >> 0 & 255, 0);
    y1 = clamp(y1, 0, SIZE_X - 1);
    y2 = clamp(y2, 0, SIZE_X - 1);
    if(y2 == y1)
 			SDL_RenderDrawPoint(ren, x, y1);
    else if(y2 > y1)
    {
		y = y1 + 1;
		SDL_RenderDrawPoint(ren, x, y1);
		while (y < y2)
		{
			SDL_RenderDrawPoint(ren, x, y);
			y++;
		}
		SDL_RenderDrawPoint(ren, x, y2);
    }
	(void)top;
	(void)bottom;
}

t_xy	intersect(float x1, float y1, float x2, float y2, float x3, float y3,float x4, float y4)
{
	t_xy ret;
	double c1;
	double c2;
	double c3;
	double c4;
	double tmp1;
	double tmp3;

	c1 = x1 - x2;
	c2 = x3 - x4;
	c3 = y1 - y2;
	c4 = y3 - y4;
	tmp1 = v_c_p(x1, y1, x2, y2);
	tmp3 = v_c_p(x3, y3, x4, y4);
	ret.y = v_c_p(tmp1, c1, tmp3, c2);
	ret.x = (ret.y / v_c_p(c1, c3, c2, c4));
	ret.y = v_c_p(tmp1, c3, tmp3, c4);
	ret.y = (ret.y / v_c_p(c1, c3,c2, c4));
	return (ret);
}

void init_vertex(t_draw *d, t_var *var, int sectorno, int s)
{
	/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
	d->vx1 = var->points[var->sectors[var->maps[0].sectors[sectorno]].pts[0 + s]].x - var->player.pos.x;
	d->vy1 = var->points[var->sectors[var->maps[0].sectors[sectorno]].pts[0 + s]].y - var->player.pos.y;
	d->vx2 = var->points[var->sectors[var->maps[0].sectors[sectorno]].pts[1 + s]].x - var->player.pos.x;
	d->vy2 = var->points[var->sectors[var->maps[0].sectors[sectorno]].pts[1 + s]].y - var->player.pos.y;
	/* Rotate them around the player's view */
	d->tx1 = d->vx1 * var->player.psin - d->vy1 * var->player.pcos;
	d->tz1 = d->vx1 * var->player.pcos + d->vy1 * var->player.psin;
	d->tx2 = d->vx2 * var->player.psin - d->vy2 * var->player.pcos;
	d->tz2 = d->vx2 * var->player.pcos + d->vy2 * var->player.psin;
}

void check_troncage(t_draw *d, t_var *var, t_xy i1, t_xy i2)
{
	if(d->tz1 < var->nearz)
	{
		if(i1.y > 0)
		{
			d->tx1 = i1.x;
			d->tz1 = i1.y;
		}
		else
		{
			d->tx1 = i2.x;
			d->tz1 = i2.y;
		}
	}
	if(d->tz2 < var->nearz)
	{
		 if(i1.y > 0)
		 {
			 d->tx2 = i1.x;
			 d->tz2 = i1.y;
		  }
		  else
		  {
			  d->tx2 = i2.x;
			  d->tz2 = i2.y;
		   }
	}
}

void draw_wals(int neighbor, SDL_Renderer *ren, t_var *var, Uint32 **wt, int yfloor, int yceil, t_draw d, int *ytop, int *ybottom)
{
	t_draw_walls dw;
	int x;
	int z;

	x = d.beginx;
	while (x++ <= d.endx)
	{
		z = ((x - d.x1) * (d.tz2 - d.tz1) / (d.x2 - d.x1) + d.tz1) * 2;
		dw.ya = (x - d.x1) * (d.y2a - d.y1a) / (d.x2 - d.x1) + d.y1a;
		dw.cya = clamp(dw.ya, ytop[x], ybottom[x]);
		dw.yb = (x - d.x1) * (d.y2b - d.y1b) / (d.x2 - d.x1) + d.y1b;
		dw.cyb = clamp(dw.yb, ytop[x], ybottom[x]);
		draw_ceiling(ren, x, ytop[x], dw.cya - 1, dw.cya, dw.cyb, var->player, wt, yfloor, yceil);
		draw_ceiling(ren, x, dw.cyb + 1, ybottom[x], dw.cya, dw.cyb, var->player, wt, yfloor, yceil);
		if(neighbor >= 0)
		{
			dw.nya = (x - d.x1) * (d.ny2a - d.ny1a) / (d.x2 - d.x1) + d.ny1a;
			dw.cnya = clamp(dw.nya, ytop[x], ybottom[x]);
			dw.nyb = (x - d.x1) * (d.ny2b - d.ny1b) / (d.x2 - d.x1) + d.ny1b;
			dw.cnyb = clamp(dw.nyb, ytop[x], ybottom[x]);
			unsigned r1 = 0x010101 * (255 - z);
			unsigned r2 = 0x040007 * (31 - z / 8);
			vline(ren, x, dw.cya, dw.cnya - 1, 0, x == d.x1 || x == d.x2 ? 0 : r1, 0);
			ytop[x] = clamp(max(dw.cya, dw.nya), ytop[x], SIZE_Y - 1);
			vline(ren, x, dw.cnyb + 1, dw.cyb, 0, x == d.x1 || x == d.x2 ? 0 : r2, 0);
			ybottom[x] = clamp(min(dw.cyb, dw.cnyb), 0, ybottom[x]);
		}
		else
		{
			z = z > 255 ? 255 : z;
			unsigned r = 0x010101 * (255 - z);
			vline(ren, x, dw.cya, dw.cyb, 0, x == d.x1 || x == d.x2 ? 0 : r, 0);
		}
	}
}

void calc_scale(t_draw *d)
{
	d->xscale1 = hfov / d->tz1;
	d->yscale1 = vfov / d->tz1;
	d->x1 = SIZE_X / 2 - (int)(d->tx1 * d->xscale1);
	d->xscale2 = hfov / d->tz2;
	d->yscale2 = vfov / d->tz2;
	d->x2 = SIZE_X / 2 - (int)(d->tx2 * d->xscale2);
}

void sectorno_and_network(t_draw *d, double yow)
{
	int s2;

	s2 = SIZE_Y / 2;
	d->y1a = s2 - (int)(yaw(d->yceil, d->tz1, yow) * d->yscale1);
	d->y1b = s2 - (int)(yaw(d->yfloor, d->tz1, yow) * d->yscale1);
	d->y2a = s2 - (int)(yaw(d->yceil, d->tz2, yow) * d->yscale2);
	d->y2b = s2 - (int)(yaw(d->yfloor, d->tz2, yow) * d->yscale2);
	d->ny1a = s2 - (int)(yaw(d->nyceil, d->tz1, yow) * d->yscale1);
	d->ny1b = s2 - (int)(yaw(d->nyfloor, d->tz1, yow) * d->yscale1);
	d->ny2a = s2 - (int)(yaw(d->nyceil, d->tz2, yow) * d->yscale2);
	d->ny2b = s2 - (int)(yaw(d->nyfloor, d->tz2, yow) * d->yscale2);
}

void calc_ny(t_draw *d, int z, t_var *var, int nei)
{
	d->nyceil = 0;
	d->nyfloor = 0;
	if (nei >= 0)
	{
		d->nyceil = var->sectors[nei].ceilling - z;
		d->nyfloor = var->sectors[nei].floor - z;
	}
}

void	troncage(t_draw *d, t_var *var)
{
	t_xy i1;
	t_xy i2;

	i1 = intersect(d->tx1, d->tz1, d->tx2, d->tz2, -var->nearside, var->nearz, -var->farside, var->farz);
	i2 = intersect(d->tx1, d->tz1, d->tx2, d->tz2, var->nearside, var->nearz, var->farside, var->farz);
	check_troncage(d, var, i1, i2);
}

void DrawScreen(t_var *var, SDL_Renderer *ren, Uint32 **wt)
{
    struct item { int sectorno,sx1,sx2; } queue[MAX_QUEUE], *head=queue, *tail=queue;
    int ytop[SIZE_X];
	int ybottom[SIZE_X];
	int renderedsectors[var->number_of_sector];
	int x;
	t_draw d;
	int neighbor;

	x = 0;
    while (x < SIZE_X)
	{
		ytop[x] = 0;
		ybottom[x] = SIZE_Y - 1;
		x++;
	}
	x = -1;
	while (++x < var->number_of_sector)
		renderedsectors[x] = 0;
    *head = (struct item) { var->player.sector, 0, SIZE_X - 1 };
    if(++head == queue + MAX_QUEUE)
		head = queue;
    while(head != tail)
	{
    	const struct item now = *tail;
    	if(++tail == queue + MAX_QUEUE)
			tail = queue;
    	if(renderedsectors[now.sectorno] & 0x21)
			continue;
    	++renderedsectors[now.sectorno];
		for (unsigned int s = 0; s < var->sectors[now.sectorno].nb_pts - 1; ++s)
    	{
			init_vertex(&d, var, now.sectorno, s);
        	if(d.tz1 <= 0 && d.tz2 <= 0)
				continue;
        	if(d.tz1 <= 0 || d.tz2 <= 0)
				troncage(&d, var);
			calc_scale(&d);
        	if(d.x1 >= d.x2 || d.x2 < now.sx1 || d.x1 > now.sx2)
				continue;
        	d.yceil = var->sectors[now.sectorno].ceilling - var->player.pos.z;
        	d.yfloor = var->sectors[now.sectorno].floor - var->player.pos.z;
        	neighbor = var->sectors[now.sectorno].neighbors[s];
			calc_ny(&d, var->player.pos.z, var, neighbor);
			sectorno_and_network(&d, var->player.yaw);
        	d.beginx = max(d.x1, now.sx1);
			d.endx = min(d.x2, now.sx2);
			draw_wals(neighbor, ren, var, wt, d.yfloor, d.yceil, d, ytop, ybottom);
        	if(neighbor >= 0 && d.endx >= d.beginx && (head + MAX_QUEUE + 1 - tail) % MAX_QUEUE)
        	{
            	*head = (struct item) { neighbor, d.beginx, d.endx };
            	if(++head == queue+MAX_QUEUE)
					head = queue;
        	}
    	}
    	++renderedsectors[now.sectorno];
    }
	SDL_RenderPresent(ren);
}
