/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:01:35 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/04 23:27:18 by vgauther         ###   ########.fr       */
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
	int ya;
	int cya;
	int yb;
	int cyb;
	int nya;
	int cnya;
	int nyb;
	int cnyb;
	
	for(int x = d.beginx; x <= d.endx; ++x)
	{
		/* Calculate the Z coordinate for this point. (Only used for lighting.) */
		int z = ((x - d.x1) * (d.tz2 - d.tz1) / (d.x2 - d.x1) + d.tz1) * 2;
		/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
		ya = (x - d.x1) * (d.y2a - d.y1a) / (d.x2 - d.x1) + d.y1a;
		cya = clamp(ya, ytop[x], ybottom[x]); // top
		yb = (x - d.x1) * (d.y2b - d.y1b) / (d.x2 - d.x1) + d.y1b;
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
			nya = (x - d.x1) * (d.ny2a - d.ny1a) / (d.x2 - d.x1) + d.ny1a;
			cnya = clamp(nya, ytop[x], ybottom[x]);
			nyb = (x - d.x1) * (d.ny2b - d.ny1b) / (d.x2 - d.x1) + d.ny1b;
			cnyb = clamp(nyb, ytop[x], ybottom[x]);
			/* If our ceiling is higher than their ceiling, render upper wall */
			unsigned r1 = 0x010101 * (255 - z);
			unsigned r2 = 0x040007 * (31 - z / 8);
			vline(ren, x, cya, cnya - 1, 0, x == d.x1 || x == d.x2 ? 0 : r1, 0); // Between our and their ceiling
			ytop[x] = clamp(max(cya, cnya), ytop[x], SIZE_Y - 1);   // Shrink the remaining window below these ceilings
			/* If our floor is lower than their floor, render bottom wall */
			vline(ren, x, cnyb + 1, cyb, 0, x == d.x1 || x == d.x2 ? 0 : r2, 0); // Between their and our floor
			ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
		}
		else
		{
			/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
			z = z > 255 ? 255 : z;
			unsigned r = 0x010101 * (255 - z);
			vline(ren, x, cya, cyb, 0, x == d.x1 || x == d.x2 ? 0 : r, 0);
		}
	}
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
	t_draw d;
	double xscale1;
	double yscale1;
	double xscale2;
	double yscale2;


	int neighbor;
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
    if(++head == queue + MaxQueue)
		head = queue;

    while(head != tail)
	{
    /* Pick a sector & slice from the queue to draw */
    const struct item now = *tail;
    if(++tail == queue + MaxQueue)
		tail = queue;
    if(renderedsectors[now.sectorno] & 0x21)
		continue; // Odd = still rendering, 0x20 = give up
    ++renderedsectors[now.sectorno];
	//const struct sector* const sect = &sectors[now.sectorno];
    /* Render each wall of this sector that is facing towards player. */
	for(unsigned int s = 0; s < var->sectors[now.sectorno].nb_pts - 1; ++s)
    {
		init_vertex(&d, var, now.sectorno, s);
        /* Is the wall at least partially in front of the player? */
        if(d.tz1 <= 0 && d.tz2 <= 0)
			continue;
        /* If it's partially behind the player, clip it against player's view frustrum */
        if(d.tz1 <= 0 || d.tz2 <= 0)
        {
            // Find an intersection between the wall and the approximate edges of player's view
            i1 = intersect(d.tx1, d.tz1, d.tx2, d.tz2, -var->nearside, var->nearz, -var->farside, var->farz);
            i2 = intersect(d.tx1, d.tz1, d.tx2, d.tz2, var->nearside, var->nearz, var->farside, var->farz);
			check_troncage(&d, var, i1, i2);
		}
        /* Do perspective transformation */
        xscale1 = hfov / d.tz1;
		yscale1 = vfov / d.tz1;
		d.x1 = SIZE_X / 2 - (int)(d.tx1 * xscale1);
        xscale2 = hfov / d.tz2;
		yscale2 = vfov / d.tz2;
		d.x2 = SIZE_X / 2 - (int)(d.tx2 * xscale2);
        if(d.x1 >= d.x2 || d.x2 < now.sx1 || d.x1 > now.sx2)
			continue; // Only render if it's visible
        /* Acquire the floor and ceiling heights, relative to where the player's view is */
        yceil = var->sectors[now.sectorno].ceilling - var->player.pos.z;
        yfloor = var->sectors[now.sectorno].floor - var->player.pos.z;
        /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
        neighbor = var->sectors[now.sectorno].neighbors[s];
        nyceil = 0;
		nyfloor = 0;
        if (neighbor >= 0) // Is another sector showing through this portal?
        {
            nyceil = var->sectors[neighbor].ceilling - var->player.pos.z;
            nyfloor = var->sectors[neighbor].floor - var->player.pos.z;
        }
        /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
        d.y1a = SIZE_Y / 2 - (int)(yaw(yceil, d.tz1, var->player.yaw) * yscale1);
		d.y1b = SIZE_Y / 2 - (int)(yaw(yfloor, d.tz1, var->player.yaw) * yscale1);
        d.y2a = SIZE_Y / 2 - (int)(yaw(yceil, d.tz2, var->player.yaw) * yscale2);
		d.y2b = SIZE_Y / 2 - (int)(yaw(yfloor, d.tz2, var->player.yaw) * yscale2);
        /* The same for the neighboring sector */
        d.ny1a = SIZE_Y / 2 - (int)(yaw(nyceil, d.tz1, var->player.yaw) * yscale1);
		d.ny1b = SIZE_Y / 2 - (int)(yaw(nyfloor, d.tz1, var->player.yaw) * yscale1);
        d.ny2a = SIZE_Y / 2 - (int)(yaw(nyceil, d.tz2, var->player.yaw) * yscale2);
		d.ny2b = SIZE_Y / 2 - (int)(yaw(nyfloor, d.tz2, var->player.yaw) * yscale2);

        /* Render the wall. */
        d.beginx = max(d.x1, now.sx1);
		d.endx = min(d.x2, now.sx2);
		draw_wals(neighbor, ren, var, wt, yfloor, yceil, d, ytop, ybottom);
        /* Schedule the neighboring sector for rendering within the window formed by this wall. */
        if(neighbor >= 0 && d.endx >= d.beginx && (head + MaxQueue + 1 - tail) % MaxQueue)
        {
            *head = (struct item) { neighbor, d.beginx, d.endx };
            if(++head == queue+MaxQueue) head = queue;
        }
    } // for s in sector's edges
    ++renderedsectors[now.sectorno];
    }  // render any other queued sectors
	SDL_RenderPresent(ren);
}
