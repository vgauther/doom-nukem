/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/15 18:59:02 by vgauther         ###   ########.fr       */
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
	coor.x = (coor.z / v_c_p(x1 - x2, y1 - y2, x3 - x4,
		y3 - y4));
	tmp1 = v_c_p(x1, y1, x2, y2);
	tmp2 = y1 - y2;
	tmp3 = v_c_p(x3, y3, x4, y4);
	tmp4 = y3 - y4;
	coor.z = v_c_p(tmp1, tmp2, tmp3, tmp4);
	coor.y = (coor.z / v_c_p(x1 - x2, y1 - y2, x3 - x4,
		y3 - y4));
	coor.z = 0;
	return (coor);
}

// int clamp(int a, int b, int c)
// {
// 	if (b > a && a < c)
// 		return (a);
// 	if (a > b && b < c)
// 		return (b);
// 	return (c);
// }

static void vline(t_var *var, int x, int y1, int y2, int r, int v, int bb)
{
	if (bb == -1)
		SDL_SetRenderDrawColor(var->sdl.render, r, v, 0, 0);
	else
		SDL_SetRenderDrawColor(var->sdl.render, 200, 200, 200, 0);

		//SDL_SetRenderDrawColor(var->sdl.render,  bb >> 16 & 255, bb >> 8 & 255, bb >> 0 & 255, 0);

    y1 = (int)clamp(y1, 0, SIZE_Y-1);
    y2 = (int)clamp(y2, 0, SIZE_Y-1);
	//if (bb != -1)
		//printf("%d | %d\n", y1, y2);
    if(y2 == y1)
		SDL_RenderDrawPoint(var->sdl.render, x, y1);
    else if(y2 > y1)
    {
		if (bb != -1)
			printf("%s\n", "le mur");
        for(int y=y1+1; y<y2; ++y)
		{
			SDL_RenderDrawPoint(var->sdl.render, x, y);
		}
    }
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

	pyaw = 0;

	int ytop[SIZE_X]={0}, ybottom[SIZE_X];
    for(unsigned x=0; x<SIZE_X; ++x) ybottom[x] = SIZE_Y-1;
	for (unsigned nb_wall = 0; nb_wall != 2; nb_wall++)
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
			float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
			i1 = intersect(t1.x, t1.z, t2.x, t2.z, -nearside, nearz, -farside, farz);
			i2 = intersect(t1.x, t1.z, t2.x, t2.z, nearside, nearz, farside, farz);
			if(t1.z < nearz) { if(i1.y > 0) { t1.x = i1.x; t1.z = i1.y; } else { t1.x = i2.x; t1.z = i2.y; } }
            if(t2.z < nearz) { if(i1.y > 0) { t2.x = i1.x; t2.z = i1.y; } else { t2.x = i2.x; t2.z = i2.y; } }
		}
		float xscale1 = hfov / t1.z, yscale1 = vfov / t1.z;    int x1 = SIZE_X/2 - (int)(t1.x * xscale1);
    	float xscale2 = hfov / t2.z, yscale2 = vfov / t2.z;    int x2 = SIZE_X/2 - (int)(t2.x * xscale2);
		if(x1 >= x2 || x2 < 0 || x1 > SIZE_X - 1) continue; // Only render if it's visible
		float yceil  = 50;
		float yfloor = 0 - var->player.pos.z;
		#define Yaw(y,z) (y + z*pyaw)
		int y1a  = SIZE_Y/2 - (int)(Yaw(yceil, t1.z) * yscale1),  y1b = SIZE_Y/2 - (int)(Yaw(yfloor, t1.z) * yscale1);
        int y2a  = SIZE_Y/2 - (int)(Yaw(yceil, t2.z) * yscale2),  y2b = SIZE_Y/2 - (int)(Yaw(yfloor, t2.z) * yscale2);

		int beginx = max(x1, 0), endx = min(x2, SIZE_X - 1);
		for(int x = beginx; x <= endx; ++x)
        {
            /* Calculate the Z coordinate for this point. (Only used for lighting.) */
            int z = ((x - x1) * (t2.z-t1.z) / (x2-x1) + t1.z) * 8;
            /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
            int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[x],ybottom[x]); // top
            int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[x],ybottom[x]); // bottom

            /* Render ceiling: everything above this sector's ceiling height. */
            vline(var, x, ytop[x], cya-1, 200, 0, -1);
			//printf("%d | %d | %d\n", cya, cyb, x);
            /* Render floor: everything below this sector's floor height. */
            vline(var, x, cyb+1, ybottom[x], 0, 200, -1);
            unsigned r = 0x010101 * (255-z);
            vline(var, x, cya, cyb, 100, 100, x==x1||x==x2 ? 0 : r);
        }
		SDL_RenderPresent(var->sdl.render);
	}
}

void init_map(t_var *var)
{
		var->map[0].x = 0;
		var->map[0].y = 0;
		var->map[1].x = 100;
		var->map[1].y = 0;
		var->map[2].x = 100;
		var->map[2].y = 100;
		var->map[3].x = 0;
		var->map[3].y = 100;
}



void	display(t_var *var)
{
	while (SDL_WaitEvent(&var->sdl.event))
	{
		if (var->sdl.event.type == SDL_QUIT)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.key.keysym.sym == SDLK_ESCAPE)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.key.keysym.sym == SDLK_RETURN)
		{
			sdl_clean_screen(var->sdl.render);
			ft_putstr("---------------\n");
			 init_map(var);
			 neo_display(var);
			 var->player.angle += (6 * RAD);
			 var->player.pcos = cos(var->player.angle);
			 var->player.psin = sin(var->player.angle);
			 printf("|%f|\n", var->player.angle);
		}
		else if (var->sdl.event.key.keysym.sym == SDLK_v)
		{
			sdl_clean_screen(var->sdl.render);
			ft_putstr("---------------\n");
			 init_map(var);
			 neo_display(var);
			 var->player.pos.x++;
			 printf("|%f|\n", var->player.angle);
		}
	}
}
