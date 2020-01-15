/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:07:51 by vgauther          #+#    #+#             */
/*   Updated: 2020/01/14 16:28:53 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int point_ceil_floor(SDL_Renderer *ren, int x, double cy1, Uint32 t)
{
	SDL_SetRenderDrawColor(ren, t >> 16 & 255, t >> 8 & 255, t >> 0 & 255, 0);
	SDL_RenderDrawPoint(ren, x, cy1);
	cy1++;
	return (cy1);
}

void draw_ceiling(SDL_Renderer *ren, int x, int y1, int y2, int cya, int cyb, t_player p, Uint32 **textur, int floor, int ceil)
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
	int w_tex;
	int h_tex;

    cy1 = (int)clamp(y1, 0, SIZE_Y - 1);
    cy2 = (int)clamp(y2, 0, SIZE_Y - 1);
	w_tex = 128;
	h_tex = 128;
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
			x_tex = (map_x > 0) ? (map_x * w_tex) / 6 : 0;
			y_tex = (map_y > 0) ? (map_y * w_tex) / 6 : 0;
			tmp = (y_tex % h_tex) * w_tex + (x_tex % w_tex);
			cy1 = point_ceil_floor(ren, x, cy1, textur[1][tmp]);
		}
    }
}
