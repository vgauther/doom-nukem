/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:01:35 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/04 17:31:58 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#define W 608
#define H 480
// double yaw(double a, double b, double c)
// {
// 	return (a + b * c);
// }

static unsigned NumSectors = 2;


double v_c_p(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - x2 * y1);
}

static void vline(SDL_Renderer *ren, int x, int y1,int y2, int top,int middle,int bottom)
{
	SDL_SetRenderDrawColor(ren, middle >> 16 & 255, middle >> 8 & 255, middle >> 0 & 255, 0);
    y1 = clamp(y1, 0, H-1);
    y2 = clamp(y2, 0, H-1);
    if(y2 == y1)
 			SDL_RenderDrawPoint(ren, x, y1);
    else if(y2 > y1)
    {
		SDL_RenderDrawPoint(ren, x, y1);
        for(int y=y1+1; y<y2; ++y)
			SDL_RenderDrawPoint(ren, x, y);
		SDL_RenderDrawPoint(ren, x, y2);
    }
	(void)top;
	(void)bottom;
}

// static void vline(SDL_Renderer *ren, int x, int y1, int y2, int r, int v, int b)
// {
// 	int y;
//
// 	SDL_SetRenderDrawColor(ren, r, v, b, 0);
//     y1 = (int)clamp(y1, 0, SIZE_Y - 1);
//     y2 = (int)clamp(y2, 0, SIZE_Y - 1);
//     if(y2 >= y1)
//     {
// 		y = y1;
//         while(y <= y2)
// 		{
// 			SDL_RenderDrawPoint(ren, x, y);
// 			y++;
// 		}
//     }
// }

t_xy	intersect(float x1, float y1, float x2, float y2, float x3, float y3,float x4, float y4)
{
	t_coor coor;
	float tmp1;
	float tmp2;
	float tmp3;
	float tmp4;

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
	t_xy ret;

	ret.x = coor.x;
	ret.y = coor.y;
	return (ret);
}

void DrawScreen(t_var *var, SDL_Renderer *ren)
{
	t_xy i1;
	t_xy i2;
    enum { MaxQueue = 32 };  // maximum number of pending portal renders
    struct item { int sectorno,sx1,sx2; } queue[MaxQueue], *head=queue, *tail=queue;
    int ytop[W]={0}, ybottom[W], renderedsectors[NumSectors];
    for(unsigned x=0; x<W; ++x) ybottom[x] = H-1;
    for(unsigned n=0; n<NumSectors; ++n) renderedsectors[n] = 0;

    /* Begin whole-screen rendering from where the player is. */
    *head = (struct item) { var->player.sector, 0, W-1 };
    if(++head == queue+MaxQueue) head = queue;

    do {
    /* Pick a sector & slice from the queue to draw */
    const struct item now = *tail;
    if(++tail == queue+MaxQueue) tail = queue;

    if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
    ++renderedsectors[now.sectorno];
    /* Render each wall of this sector that is facing towards player. */
	ft_putstr("changement de secteur\n");
	for(unsigned s = 0; s < var->sectors[now.sectorno].nb_pts - 1; ++s)
    {
		ft_putstr("nb de pts dan le secteur\n");
		ft_putnbr(var->sectors[now.sectorno].nb_pts);
		ft_putstr("error2\n");
        /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
        float vx1 = var->points[var->sectors[var->maps[0].sectors[now.sectorno]].pts[0 + s]].x - var->player.pos.x;
		float vy1 = var->points[var->sectors[var->maps[0].sectors[now.sectorno]].pts[0 + s]].y - var->player.pos.y;
        float vx2 = var->points[var->sectors[var->maps[0].sectors[now.sectorno]].pts[1 + s]].x - var->player.pos.x;
		float vy2 = var->points[var->sectors[var->maps[0].sectors[now.sectorno]].pts[1 + s]].y - var->player.pos.y;
        /* Rotate them around the player's view */
		ft_putstr("error3\n");
		float pcos = var->player.pcos;
		float psin = var->player.psin;
        float tx1 = vx1 * psin - vy1 * pcos;
		float tz1 = vx1 * pcos + vy1 * psin;
        float tx2 = vx2 * psin - vy2 * pcos;
		float tz2 = vx2 * pcos + vy2 * psin;
        /* Is the wall at least partially in front of the player? */
        if(tz1 <= 0 && tz2 <= 0) continue;
        /* If it's partially behind the player, clip it against player's view frustrum */
        if(tz1 <= 0 || tz2 <= 0)
        {
            float nearz = 1e-4f;
			float farz = 5;
			float nearside = 1e-5f;
			float farside = 20.f;
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
        float xscale1 = hfov / tz1;
		float yscale1 = vfov / tz1;
		int x1 = W/2 - (int)(tx1 * xscale1);
        float xscale2 = hfov / tz2;
		float yscale2 = vfov / tz2;
		int x2 = W/2 - (int)(tx2 * xscale2);
        if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue; // Only render if it's visible
        /* Acquire the floor and ceiling heights, relative to where the player's view is */
        float yceil = var->sectors[now.sectorno].ceilling - var->player.pos.z;
        float yfloor = var->sectors[now.sectorno].floor - var->player.pos.z;
        /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
        int neighbor = var->sectors[now.sectorno].neighbors[s];
        float nyceil = 0;
		float nyfloor = 0;
        if(neighbor >= 0) // Is another sector showing through this portal?
        {
            nyceil = var->sectors[neighbor].ceilling - var->player.pos.z;
            nyfloor = var->sectors[neighbor].floor - var->player.pos.z;
        }
        /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
        #define Yaw(y,z) (y + z*var->player.yaw)
        int y1a  = H/2 - (int)(Yaw(yceil, tz1) * yscale1);
		int y1b = H/2 - (int)(Yaw(yfloor, tz1) * yscale1);
        int y2a  = H/2 - (int)(Yaw(yceil, tz2) * yscale2);
		int y2b = H/2 - (int)(Yaw(yfloor, tz2) * yscale2);
        /* The same for the neighboring sector */
        int ny1a = H/2 - (int)(Yaw(nyceil, tz1) * yscale1);
		int ny1b = H/2 - (int)(Yaw(nyfloor, tz1) * yscale1);
        int ny2a = H/2 - (int)(Yaw(nyceil, tz2) * yscale2);
		int ny2b = H/2 - (int)(Yaw(nyfloor, tz2) * yscale2);

        /* Render the wall. */
        int beginx = max(x1, now.sx1);
		int endx = min(x2, now.sx2);
        for(int x = beginx; x <= endx; ++x)
        {
            /* Calculate the Z coordinate for this point. (Only used for lighting.) */
            int z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
            /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
            int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a;
			int cya = clamp(ya, ytop[x],ybottom[x]); // top
            int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b;
			int cyb = clamp(yb, ytop[x],ybottom[x]); // bottom

            /* Render ceiling: everything above this sector's ceiling height. */
            vline(ren, x, ytop[x], cya-1, 0x111111 ,0x222222,0x111111);
            /* Render floor: everything below this sector's floor height. */
            vline(ren, x, cyb+1, ybottom[x], 0x0000FF,0x0000AA,0x0000FF);

            /* Is there another sector behind this edge? */
            if(neighbor >= 0)
            {
                /* Same for _their_ floor and ceiling */
                int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a;
				int cnya = clamp(nya, ytop[x],ybottom[x]);
                int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b;
				int cnyb = clamp(nyb, ytop[x],ybottom[x]);
                /* If our ceiling is higher than their ceiling, render upper wall */
                unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
                vline(ren, x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0); // Between our and their ceiling
                ytop[x] = clamp(max(cya, cnya), ytop[x], H-1);   // Shrink the remaining window below these ceilings
                /* If our floor is lower than their floor, render bottom wall */
                vline(ren, x, cnyb+1, cyb, 0, x==x1||x==x2 ? 0 : r2, 0); // Between their and our floor
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
        if(neighbor >= 0 && endx >= beginx && (head+MaxQueue+1-tail)%MaxQueue)
        {
            *head = (struct item) { neighbor, beginx, endx };
            if(++head == queue+MaxQueue) head = queue;
        }
    } // for s in sector's edges
    ++renderedsectors[now.sectorno];
    } while(head != tail); // render any other queued sectors
	SDL_RenderPresent(ren);
}
