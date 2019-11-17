/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/17 11:09:54 by vgauther         ###   ########.fr       */
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

double yaw(double a, double b, double c)
{
	return (a + b * c);
}

void neo_display(t_var *var)
{
	t_coor v1;
	t_coor v2;
	t_coor t1;
	t_coor t2;
	t_coor i1;
	t_coor i2;
	float pyaw;
	float xscale1;
	float yscale1;
	float xscale2;
	float yscale2;
	int beginx;
	int endx;
	float nearz = 1e-4f;
	float farz = 5;
	float nearside = 1e-5f;
	float farside = 20.f;
	int ytop[SIZE_X]={0};
	int ybottom[SIZE_X];
	int x1;
	int x2;

	pyaw = 0;
    for(unsigned x=0; x < SIZE_X; ++x) ybottom[x] = SIZE_Y-1;
	for (unsigned nb_wall = 0; nb_wall != 5; nb_wall++)
	{
		v1.x = var->map[0 + nb_wall].x - var->player.pos.x;
		v1.y = var->map[0 + nb_wall].y - var->player.pos.y;
		v2.x = var->map[1 + nb_wall].x - var->player.pos.x;
		v2.y = var->map[1 + nb_wall].y - var->player.pos.y;
		t1.x = v1.x * var->player.psin - v1.y * var->player.pcos;
		t1.z = v1.x * var->player.pcos + v1.y * var->player.psin;
		t2.x = v2.x * var->player.psin - v2.y * var->player.pcos;
		t2.z = v2.x * var->player.pcos + v2.y * var->player.psin;
		if(t1.z <= 0 && t2.z <= 0)
			continue;
		if(t1.z <= 0 || t2.z <= 0)
		{
			i1 = intersect(t1.x, t1.z, t2.x, t2.z, -nearside, nearz, -farside, farz);
			i2 = intersect(t1.x, t1.z, t2.x, t2.z, nearside, nearz, farside, farz);
			if(t1.z < nearz)
			{
				if(i1.y > 0)
				{
					t1.x = i1.x; t1.z = i1.y;
				}
				else
				{
					t1.x = i2.x;
					t1.z = i2.y;
				}
			}
            if(t2.z < nearz)
			{
				if(i1.y > 0)
				{
					t2.x = i1.x;
					t2.z = i1.y;
				}
				else
				{
					t2.x = i2.x;
					t2.z = i2.y;
				}
			}
		}
		xscale1 = hfov / t1.z;
		yscale1 = vfov / t1.z;
		x1 = SIZE_X/2 - (int)(t1.x * xscale1);
    	xscale2 = hfov / t2.z;
		yscale2 = vfov / t2.z;
		x2 = SIZE_X/2 - (int)(t2.x * xscale2);
		if(x1 >= x2 || x2 < 0 || x1 > SIZE_X - 1) continue; // Only render if it's visible
		float yceil  = 12;
		float yfloor = 0 - var->player.pos.z;
		int y1a = SIZE_Y/2 - (int)(yaw(yceil, t1.z, pyaw) * yscale1);
		int y1b = SIZE_Y/2 - (int)(yaw(yfloor, t1.z, pyaw) * yscale1);
        int y2a = SIZE_Y/2 - (int)(yaw(yceil, t2.z, pyaw) * yscale2);
		int y2b = SIZE_Y/2 - (int)(yaw(yfloor, t2.z, pyaw) * yscale2);
		beginx = max(x1, 0);
		endx = min(x2, SIZE_X - 1);
		for(int x = beginx; x <= endx; ++x)
        {
            int z = ((x - x1) * (t2.z-t1.z) / (x2-x1) + t1.z) * 8;
            int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a;
			int cya = clamp(ya, ytop[x],ybottom[x]); // top
            int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b;
			int cyb = clamp(yb, ytop[x],ybottom[x]); // bottom
            vline(var, x, ytop[x], cya-1, 200, 0, -1);
            vline(var, x, cyb+1, ybottom[x], 0, 200, -1);
            unsigned r = 0x010101 * (255-z);
			if (nb_wall == 0)
				vline(var, x, cya, cyb, 255, 70, x==x1||x==x2 ? 0 : r);
			else if (nb_wall == 1)
				vline(var, x, cya, cyb, 70, 255, x==x1||x==x2 ? 0 : r);
			else if (nb_wall == 2)
				vline(var, x, cya, cyb, 100, 100, x==x1||x==x2 ? 0 : r);
			else if (nb_wall == 3)
				vline(var, x, cya, cyb, 0, 150, x==x1||x==x2 ? 0 : r);
			else
				vline(var, x, cya, cyb, 0, 0, x==x1||x==x2 ? 0 : r);
        }
	}
	SDL_RenderPresent(var->sdl.render);
}

void	display(t_var *var)
{
	while (SDL_WaitEvent(&var->sdl.event))
	{
		if (var->sdl.event.type == SDL_QUIT)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.key.keysym.sym == SDLK_ESCAPE)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.key.keysym.sym == SDLK_d)
		{
			sdl_clean_screen(var->sdl.render);
			neo_display(var);
			var->player.angle += 6;
			var->player.pcos = cos(var->player.angle * RAD);
			var->player.psin = sin(var->player.angle * RAD);
		}
		else if (var->sdl.event.key.keysym.sym == SDLK_a)
		{
			sdl_clean_screen(var->sdl.render);
			neo_display(var);
			var->player.angle -= 6;
			var->player.pcos = cos(var->player.angle * RAD);
			var->player.psin = sin(var->player.angle * RAD);
		}
	}
}
