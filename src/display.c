/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:01:35 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/04 22:08:43 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// double yaw(double a, double b, double c)
// {
// 	return (a + b * c);
// }

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

void DrawScreen(t_var *var, SDL_Renderer *ren, Uint32 **wt)
{
	int NumSectors = 2;
	t_xy i1;
	t_xy i2;
	int MaxQueue = 32;  // maximum number of pending portal renders
    struct item { int sectorno,sx1,sx2; } queue[MaxQueue], *head=queue, *tail=queue;
    int ytop[SIZE_X];
	int ybottom[SIZE_X];
	int renderedsectors[NumSectors];
	int x;
	double vx1;
	double vy1;
	double vx2;
	double vy2;
	double tx1;
	double tz1;
	double tx2;
	double tz2;
	int y1a;
	int y1b;
	int y2a;
	int y2b;
	int ny1a;
	int ny1b;
	int ny2a;
	int ny2b;
	double xscale1;
	double yscale1;
	int x1;
	double xscale2;
	double yscale2;
	int x2;
	int beginx;
	int endx;
	int ya;
	int cya;
	int yb;
	int cyb;
	int nya;
	int cnya;
	int nyb;
	int cnyb;
	int neighbor;
	double nearz;
	double farz;
	double nearside;
	double farside;
	double nyceil;
	double nyfloor;
	double yceil;
	double yfloor;

	x = 0;
    while (x < SIZE_X)
	{
		ytop[x] = 0;
		ybottom[x] = SIZE_Y - 1;
		x++;
	}
	x = 0;
	while (x < NumSectors)
	{
		renderedsectors[x] = 0;
		x++;
	}
    /* Begin whole-screen rendering from where the player is. */
    *head = (struct item) { var->player.sector, 0, SIZE_X - 1 };
    if(++head == queue + MaxQueue) head = queue;

    do {
    /* Pick a sector & slice from the queue to draw */
    const struct item now = *tail;
    if(++tail == queue+MaxQueue) tail = queue;

    if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
    ++renderedsectors[now.sectorno];
	//const struct sector* const sect = &sectors[now.sectorno];
    /* Render each wall of this sector that is facing towards player. */
	for(unsigned s = 0; s < var->sectors[now.sectorno].nb_pts - 1; ++s)
    {
        /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
        vx1 = var->points[var->sectors[var->maps[0].sectors[now.sectorno]].pts[0 + s]].x - var->player.pos.x;
		vy1 = var->points[var->sectors[var->maps[0].sectors[now.sectorno]].pts[0 + s]].y - var->player.pos.y;
        vx2 = var->points[var->sectors[var->maps[0].sectors[now.sectorno]].pts[1 + s]].x - var->player.pos.x;
		vy2 = var->points[var->sectors[var->maps[0].sectors[now.sectorno]].pts[1 + s]].y - var->player.pos.y;
        /* Rotate them around the player's view */
        tx1 = vx1 * var->player.psin - vy1 * var->player.pcos;
		tz1 = vx1 * var->player.pcos + vy1 * var->player.psin;
        tx2 = vx2 * var->player.psin - vy2 * var->player.pcos;
		tz2 = vx2 * var->player.pcos + vy2 * var->player.psin;
        /* Is the wall at least partially in front of the player? */
        if(tz1 <= 0 && tz2 <= 0) continue;
        /* If it's partially behind the player, clip it against player's view frustrum */
        if(tz1 <= 0 || tz2 <= 0)
        {
            nearz = 1e-4f;
			farz = 5;
			nearside = 1e-5f;
			farside = 20.f;
            // Find an intersection between the wall and the approximate edges of player's view
            i1 = intersect(tx1,tz1,tx2,tz2, -nearside, nearz, -farside, farz);
            i2 = intersect(tx1,tz1,tx2,tz2,  nearside, nearz,  farside, farz);
            if(tz1 < nearz)
			{
				if(i1.y > 0)
				{
					tx1 = i1.x;
					tz1 = i1.y;
				}
				else
				{
					tx1 = i2.x;
					tz1 = i2.y;
				}
			}
            if(tz2 < nearz)
			{
				 if(i1.y > 0)
				 {
					 tx2 = i1.x;
					 tz2 = i1.y;
				  }
				  else
				  {
					   tx2 = i2.x;
					   tz2 = i2.y;
				   }
			}
        }
        /* Do perspective transformation */
        xscale1 = hfov / tz1;
		yscale1 = vfov / tz1;
		x1 = SIZE_X / 2 - (int)(tx1 * xscale1);
        xscale2 = hfov / tz2;
		yscale2 = vfov / tz2;
		x2 = SIZE_X / 2 - (int)(tx2 * xscale2);
        if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue; // Only render if it's visible
        /* Acquire the floor and ceiling heights, relative to where the player's view is */
        yceil = var->sectors[now.sectorno].ceilling - var->player.pos.z;
        yfloor = var->sectors[now.sectorno].floor - var->player.pos.z;
        /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
        neighbor = var->sectors[now.sectorno].neighbors[s];
        nyceil = 0;
		nyfloor = 0;
        if(neighbor >= 0) // Is another sector showing through this portal?
        {
            nyceil = var->sectors[neighbor].ceilling - var->player.pos.z;
            nyfloor = var->sectors[neighbor].floor - var->player.pos.z;
        }
        /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
        #define Yaw(y,z) (y + z*var->player.yaw)
        y1a = SIZE_Y / 2 - (int)(Yaw(yceil, tz1) * yscale1);
		y1b = SIZE_Y / 2 - (int)(Yaw(yfloor, tz1) * yscale1);
        y2a = SIZE_Y / 2 - (int)(Yaw(yceil, tz2) * yscale2);
		y2b = SIZE_Y / 2 - (int)(Yaw(yfloor, tz2) * yscale2);
        /* The same for the neighboring sector */
        ny1a = SIZE_Y / 2 - (int)(Yaw(nyceil, tz1) * yscale1);
		ny1b = SIZE_Y / 2 - (int)(Yaw(nyfloor, tz1) * yscale1);
        ny2a = SIZE_Y / 2 - (int)(Yaw(nyceil, tz2) * yscale2);
		ny2b = SIZE_Y / 2 - (int)(Yaw(nyfloor, tz2) * yscale2);

        /* Render the wall. */
        beginx = max(x1, now.sx1);
		endx = min(x2, now.sx2);
        for(int x = beginx; x <= endx; ++x)
        {
            /* Calculate the Z coordinate for this point. (Only used for lighting.) */
            int z = ((x - x1) * (tz2 - tz1) / (x2 - x1) + tz1) * 8;
            /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
            ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
			cya = clamp(ya, ytop[x], ybottom[x]); // top
            yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
			cyb = clamp(yb, ytop[x], ybottom[x]); // bottom

            /* Render ceiling: everything above this sector's ceiling height. */
            //vline(ren, x, ytop[x], cya - 1, 0x111111, 0x222222, 0x111111);
			draw_ceiling(ren, x, ytop[x], cya - 1, cya, cyb, var->player, wt, yfloor, yceil);

            /* Render floor: everything below this sector's floor height. */
			draw_ceiling(ren, x, cyb + 1, ybottom[x], cya, cyb, var->player, wt, yfloor, yceil);

            //vline(ren, x, cyb + 1, ybottom[x], 0x0000FF, 0x0000AA, 0x0000FF);

            /* Is there another sector behind this edge? */
            if(neighbor >= 0)
            {
                /* Same for _their_ floor and ceiling */
                nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
				cnya = clamp(nya, ytop[x], ybottom[x]);
                nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
				cnyb = clamp(nyb, ytop[x], ybottom[x]);
                /* If our ceiling is higher than their ceiling, render upper wall */
                unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
                vline(ren, x, cya, cnya - 1, 0, x == x1 || x == x2 ? 0 : r1, 0); // Between our and their ceiling
                ytop[x] = clamp(max(cya, cnya), ytop[x], SIZE_Y - 1);   // Shrink the remaining window below these ceilings
                /* If our floor is lower than their floor, render bottom wall */
                vline(ren, x, cnyb + 1, cyb, 0, x == x1 || x == x2 ? 0 : r2, 0); // Between their and our floor
                ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
            }
            else
            {
                /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                unsigned r = 0x010101 * (255-z);
                vline(ren, x, cya, cyb, 0, x==x1||x==x2 ? 0 : r, 0);
            }
        }
        /* Schedule the neighboring sector for rendering within the window formed by this wall. */
        if(neighbor >= 0 && endx >= beginx && (head + MaxQueue + 1 - tail) % MaxQueue)
        {
            *head = (struct item) { neighbor, beginx, endx };
            if(++head == queue+MaxQueue) head = queue;
        }
    } // for s in sector's edges
    ++renderedsectors[now.sectorno];
    } while(head != tail); // render any other queued sectors
	SDL_RenderPresent(ren);
}
