/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:24:03 by vgauther          #+#    #+#             */
/*   Updated: 2020/01/16 15:21:04 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void select_key_to_edit(SDL_Event ev, t_var *var)
{
	if (ev.motion.y > SIZE_Y / 2 - 100 && ev.motion.y < SIZE_Y / 2 - 20)
	{
		ft_putstr("Right\n");
		var->index_key = MV_RIGHT;
	}
	else if (ev.motion.y > SIZE_Y / 2 - 5 && ev.motion.y < SIZE_Y / 2 + 60)
	{
		ft_putstr("Left\n");
		var->index_key = MV_LEFT;
	}
	else if (ev.motion.y > SIZE_Y / 2 + 70 && ev.motion.y < SIZE_Y / 2 + 145)
	{
		ft_putstr("Forward\n");
		var->index_key = MV_FORWARD;
	}
	else if (ev.motion.y > SIZE_Y / 2 + 155 && ev.motion.y < SIZE_Y / 2 + 230)
	{
		ft_putstr("Backward\n");
		var->index_key = MV_BACKWARD;
	}
}

static void pressed_key_attributed(const Uint8 *inkeys, t_var *var)
{
	int yo;

	yo = 0;
	while (inkeys[yo] == 0)
		yo++;
	if (inkeys[yo])
	{
		var->key[var->index_key] = yo;
		var->index_key = -1;
	}
}

void option(SDL_Renderer *ren, t_var *var, SDL_Event ev, const Uint8 *inkeys)
{
	int test_x = (2560 / 2 - SIZE_X / 2) * -1;
	int test_y = (1440 / 2 - SIZE_Y / 2) * -1;

	put_surface(ren, var->option_menu, create_sdl_rect(test_x, test_y, 0, 0));
	if (ev.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ev.motion.x > SIZE_X / 2 && ev.motion.x < SIZE_X)
		{
			select_key_to_edit(ev, var);
		}
		else if (ev.motion.x > 0 && ev.motion.x < 100 && ev.motion.y > 0 && ev.motion.y < 100)
		{
			var->kind_of_screen = SCREEN_ID_MENU;
			ft_putstr("Return Menu\n");
			main_menu_g(ev, ren, test_x, test_y, var, inkeys);
		}
	}
	else if (ev.type == SDL_KEYDOWN && var->index_key != -1)
		pressed_key_attributed(inkeys, var);
}
