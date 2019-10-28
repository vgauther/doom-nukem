/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 17:12:07 by ravernhe          #+#    #+#             */
/*   Updated: 2019/10/16 12:57:42 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		init_a_b_alpha(t_pos *a, t_pos *b, double *alpha)
{
	a->x = 10000;
	a->y = 10000;
	b->x = 10000;
	b->y = 10000;
	*alpha = *alpha * RAD;
}

/*
** inter->dist = (inter->dist == 0) ? 1 : inter->dist;
*/

static void	calc_hei_column(t_var *var, t_inter *inter, t_player *player)
{
	inter->dist = launch_ray(player, var, inter->alpha, inter->beta);
	inter->hei = BS_INT * 931 / (inter->dist + 1);
	inter->phw = SIZE_Y_2 - inter->hei / 2;
	inter->y_img = 0;
	if (inter->phw < 0)
	{
		inter->y_img = -1 * inter->phw;
		inter->phw = 0;
	}
}

static void	draw_floor(SDL_Renderer *render, t_inter *inter)
{
	SDL_SetRenderDrawColor(render, 150, 150, 150, 255);
	while (inter->phw < SIZE_Y)
	{
		SDL_RenderDrawPoint(render, inter->plw, inter->phw);
		inter->phw++;
	}
}

static void	init_inter_variables(t_inter *inter, t_player *player)
{
	inter->beta = 30.00;
	inter->plw = 0;
	inter->y_img = 0;
	inter->alpha = player->angle;
}

/*
**	phw = pos_hei_win
**	plw = pos_len_win
*/

void		print_screen(t_var *var, t_player *player)
{
	t_inter	inter;
	int		y_tmp;

	init_inter_variables(&inter, player);
	while (inter.plw != SIZE_X)
	{
		calc_hei_column(var, &inter, player);
		while (inter.phw < SIZE_Y_2 + inter.hei / 2 && inter.phw < SIZE_Y - 1)
		{
			y_tmp = (double)inter.y_img / (double)inter.hei * BS;
			var->color = get_color_from_surface(var->wall_uint[var->texture_id]
				[var->i + BS_INT * y_tmp]);
			SDL_SetRenderDrawColor(var->sdl.render, var->color.r, var->color.g,\
				var->color.b, 255);
			SDL_RenderDrawPoint(var->sdl.render, inter.plw, inter.phw);
			inter.y_img++;
			inter.phw++;
		}
		draw_floor(var->sdl.render, &inter);
		inter.alpha = inter.alpha - DIV_60_SIZE;
		inter.beta = inter.beta - DIV_60_SIZE;
		inter.plw++;
	}
	put_image(var, "./assets/menu.bmp", create_sdl_rect(750, 30, 0, 0));
	SDL_RenderPresent(var->sdl.render);
}
