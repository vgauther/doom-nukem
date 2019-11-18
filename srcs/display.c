/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/17 18:36:22 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

double v_c_p(double x1, double y1, double x2, double y2)
{
	return(x1 * y2 - x2 * y1);
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

static void vline(t_var *var, int x, int y1, int y2, int r, int v, int bb)
{
	int y;


	if (bb == -1)
		SDL_SetRenderDrawColor(var->sdl.render, r, v, 0, 0);
	else if (bb == -4)
		SDL_SetRenderDrawColor(var->sdl.render, 0, 0, 0, 0);
	else if (bb == -5)
		SDL_SetRenderDrawColor(var->sdl.render, 50, 50, 50, 0);
	else
		SDL_SetRenderDrawColor(var->sdl.render, r, v, 200, 0);
    y1 = (int)clamp(y1, 0, SIZE_Y-1);
    y2 = (int)clamp(y2, 0, SIZE_Y-1);
    if(y2 == y1)
		SDL_RenderDrawPoint(var->sdl.render, x, y1);
    else if(y2 > y1)
    {
		y = y1;
        while(y <= y2)
		{
			SDL_RenderDrawPoint(var->sdl.render, x, y);
			y++;
		}
    }
}

void init_wall_calcul(t_render *r, t_var *var, int nb_wall)
{
	r->v1.x = var->map[0 + nb_wall].x - var->player.pos.x;
	r->v1.y = var->map[0 + nb_wall].y - var->player.pos.y;
	r->v2.x = var->map[1 + nb_wall].x - var->player.pos.x;
	r->v2.y = var->map[1 + nb_wall].y - var->player.pos.y;
	r->t1.x = r->v1.x * var->player.psin - r->v1.y * var->player.pcos;
	r->t1.z = r->v1.x * var->player.pcos + r->v1.y * var->player.psin;
	r->t2.x = r->v2.x * var->player.psin - r->v2.y * var->player.pcos;
	r->t2.z = r->v2.x * var->player.pcos + r->v2.y * var->player.psin;
}

void neo_display(t_var *var)
{
	t_coor i1;
	t_coor i2;
	float pyaw;
	int beginx;
	int endx;
	int ytop[SIZE_X]={0};
	int ybottom[SIZE_X];
	t_render r;

	pyaw = 0;
	r.nearz = 1e-4f;
	r.farz = 5;
	r.nearside = 1e-5f;
	r.farside = 20.f;
    for(unsigned x=0; x < SIZE_X; ++x) ybottom[x] = SIZE_Y-1;
	for (unsigned nb_wall = 0; nb_wall != 12; nb_wall++)
	{
		init_wall_calcul(&r, var, nb_wall);
		if(r.t1.z <= 0 && r.t2.z <= 0)
			continue;
		if(r.t1.z <= 0 || r.t2.z <= 0)
		{
			i1 = intersect(r.t1.x, r.t1.z, r.t2.x, r.t2.z, -r.nearside, r.nearz, -r.farside, r.farz);
			i2 = intersect(r.t1.x, r.t1.z, r.t2.x, r.t2.z, r.nearside, r.nearz, r.farside, r.farz);
			if(r.t1.z < r.nearz)
			{
				if(i1.y > 0)
				{
					r.t1.x = i1.x;
					r.t1.z = i1.y;
				}
				else
				{
					r.t1.x = i2.x;
					r.t1.z = i2.y;
				}
			}
            if(r.t2.z < r.nearz)
			{
				if(i1.y > 0)
				{
					r.t2.x = i1.x;
					r.t2.z = i1.y;
				}
				else
				{
					r.t2.x = i2.x;
					r.t2.z = i2.y;
				}
			}
		}
		r.xscale1 = hfov / r.t1.z;
		r.yscale1 = vfov / r.t1.z;
		r.x1 = SIZE_X/2 - (int)(r.t1.x * r.xscale1);
    	r.xscale2 = hfov / r.t2.z;
		r.yscale2 = vfov / r.t2.z;
		r.x2 = SIZE_X/2 - (int)(r.t2.x * r.xscale2);
		if(r.x1 >= r.x2 || r.x2 < 0 || r.x1 > SIZE_X - 1) continue; // Only render if it's visible
		float yceil  = 32;
		float yfloor = 0 - var->player.pos.z;
		int y1a = SIZE_Y/2 - (int)(yaw(yceil, r.t1.z, pyaw) * r.yscale1);
		int y1b = SIZE_Y/2 - (int)(yaw(yfloor, r.t1.z, pyaw) * r.yscale1);
        int y2a = SIZE_Y/2 - (int)(yaw(yceil, r.t2.z, pyaw) * r.yscale2);
		int y2b = SIZE_Y/2 - (int)(yaw(yfloor, r.t2.z, pyaw) * r.yscale2);
		beginx = max(r.x1, 0);
		endx = min(r.x2, SIZE_X - 1);
		for(int x = beginx; x <= endx; ++x)
        {
            int z = ((x - r.x1) * (r.t2.z-r.t1.z) / (r.x2-r.x1) + r.t1.z) * 8;
            int ya = (x - r.x1) * (y2a-y1a) / (r.x2-r.x1) + y1a;
			int cya = clamp(ya, ytop[x],ybottom[x]); // top
            int yb = (x - r.x1) * (y2b-y1b) / (r.x2-r.x1) + y1b;
			int cyb = clamp(yb, ytop[x],ybottom[x]); // bottom
            vline(var, x, ytop[x], cya-1, 200, 0, -4);
            vline(var, x, cyb+1, ybottom[x], 0, 200, -5);
            unsigned r = 0x010101 * (255-z);
			if (nb_wall == 0)
				vline(var, x, cya, cyb, 255, 70, r);
			else if (nb_wall == 1)
				vline(var, x, cya, cyb, 70, 255, r);
			else if (nb_wall == 2)
				vline(var, x, cya, cyb, 100, 100, r);
			else if (nb_wall == 3)
				vline(var, x, cya, cyb, 0, 150, r);
			else if (nb_wall == 4)
				vline(var, x, cya, cyb, 30, 150, r);
			else if (nb_wall == 5)
				vline(var, x, cya, cyb, 200, 150, r);
			else
				vline(var, x, cya, cyb, 0, 0, -1);
        }
	}
	SDL_RenderPresent(var->sdl.render);
}

void	display(t_var *var)
{
	sdl_clean_screen(var->sdl.render);
	neo_display(var);
	while (SDL_WaitEvent(&var->sdl.event))
	{
		if (var->sdl.event.type == SDL_QUIT)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.key.keysym.sym == SDLK_ESCAPE)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.type == SDL_KEYDOWN)
		{
			if (var->sdl.event.key.keysym.sym == SDLK_d)
			{
				var->player.angle += 6;
				var->player.pcos = cos(var->player.angle * RAD);
				var->player.psin = sin(var->player.angle * RAD);
				sdl_clean_screen(var->sdl.render);
				neo_display(var);
			}
			else if (var->sdl.event.key.keysym.sym == SDLK_a)
			{
				var->player.angle -= 6;
				var->player.pcos = cos(var->player.angle * RAD);
				var->player.psin = sin(var->player.angle * RAD);
				sdl_clean_screen(var->sdl.render);
				neo_display(var);
			}
			else if (var->sdl.event.key.keysym.sym == SDLK_w)
			{
				forward(var, 4, var->player.angle);
				sdl_clean_screen(var->sdl.render);
				neo_display(var);
			}
			else if (var->sdl.event.key.keysym.sym == SDLK_s)
			{
				backward(var, 4, var->player.angle);
				sdl_clean_screen(var->sdl.render);
				neo_display(var);
			}
		}
	}
}
