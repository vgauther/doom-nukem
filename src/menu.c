/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:27:38 by vgauther          #+#    #+#             */
/*   Updated: 2020/01/16 15:39:45 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void main_menu_g(SDL_Event ev, SDL_Renderer *ren, int test_x, int test_y, t_var *var, const Uint8 *inkeys)
{
	if (ev.type == SDL_MOUSEMOTION || ev.type == SDL_MOUSEBUTTONDOWN)
	{
		put_surface(ren, var->main_menu, create_sdl_rect(test_x,test_y,0,0));
		if (ev.motion.x > SIZE_X / 2 - 210 && ev.motion.x < SIZE_X / 2 + 200)
		{
			if (ev.motion.y > SIZE_Y / 2 - 140 && ev.motion.y < SIZE_Y / 2 - 20)
			{
				put_surface(ren, var->axe, create_sdl_rect(SIZE_X / 2 - (var->axe->w / 2) - 210, SIZE_Y / 2 - (var->axe->h / 2) - 85, 0, 0));
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					var->kind_of_screen = SCREEN_ID_GAME;
					DrawScreen(var, ren, var->walll_uint);
					SDL_RenderPresent(ren);
				}
			}
			else if (ev.motion.y > SIZE_Y / 2 - 80 && ev.motion.y < SIZE_Y / 2 + 80)
			{
				put_surface(ren, var->axe, create_sdl_rect(SIZE_X / 2 - (var->axe->w / 2) - 210, SIZE_Y / 2 - 20, 0, 0));
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					var->kind_of_screen = SCREEN_ID_SELECTMAP;
					select_map(ren, ev);
				}
			}
			else if (ev.motion.y > SIZE_Y / 2 - 60 && ev.motion.y < SIZE_Y / 2 + 180)
			{
				put_surface(ren, var->axe, create_sdl_rect(SIZE_X / 2 - (var->axe->w / 2) - 300, SIZE_Y / 2 + 80, 0, 0));
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					var->kind_of_screen = SCREEN_ID_OPTION;
					option(ren, var, ev, inkeys);
				}
			}
			else if (ev.motion.y > SIZE_Y / 2 + 80 && ev.motion.y < SIZE_Y / 2 + 280)
			{
				put_surface(ren, var->axe, create_sdl_rect(SIZE_X / 2 - (var->axe->w / 2) - 210, SIZE_Y / 2 + 180, 0, 0));
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					SDL_Quit();
					exit(0);
				}
			}
		}
		SDL_RenderPresent(ren);
	}
}
