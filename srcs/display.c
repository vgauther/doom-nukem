/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:08:00 by ravernhe          #+#    #+#             */
/*   Updated: 2019/10/13 19:09:42 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	init_var_display(t_var *var, int *token)
{
	*token = 0;
	var->menu_is_act = 0;
	var->on = 0;
}

void	menu_button_in_game(t_var *var, t_player *player)
{
	int			x_y[2];

	x_y[0] = var->sdl.event.button.x;
	x_y[1] = var->sdl.event.button.y;
	sdl_clean_screen(var->sdl.render);
	print_screen(var, player);
	if (x_y[0] >= 750 && x_y[0] <= 929 && x_y[1] >= 30 && x_y[1] <= 80)
	{
		put_image(var, "./assets/menu_o.bmp", create_sdl_rect(750, 30, 0, 0));
		SDL_RenderPresent(var->sdl.render);
		if (var->on == 0)
		{
			var->menu_is_act = 0;
			sdl_clean_screen(var->sdl.render);
			ft_menu(var, player);
		}
	}
	else
		put_image(var, "./assets/menu.bmp", create_sdl_rect(750, 30, 0, 0));

}

void	display(t_var *var, t_player *pl)
{
	int token;

	init_var_display(var, &token);
	ft_menu(var, pl);
	while (SDL_WaitEvent(&var->sdl.event))
	{
		if (var->sdl.event.type == SDL_MOUSEMOTION && (var->menu_is_act == 0 || var->menu_is_act == 2))
		{
			var->on = 1;
			ft_menu(var, pl);
		}
		else if (var->sdl.event.type == SDL_MOUSEBUTTONDOWN && (var->menu_is_act == 0 || var->menu_is_act == 2))
		{
			var->on = 0;
			ft_menu(var, pl);
		}
		else if (var->sdl.event.type == SDL_QUIT)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.key.keysym.sym == SDLK_ESCAPE)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.type == SDL_KEYDOWN && var->menu_is_act == 1)
			ft_move(var->sdl.event.key.keysym.sym, pl, var->sdl.render, var);
		if (var->sdl.event.type == SDL_MOUSEMOTION && (var->menu_is_act == 1))
		{
			var->on = 1;
			menu_button_in_game(var, pl);
		}
		else if (var->sdl.event.type == SDL_MOUSEBUTTONDOWN && (var->menu_is_act == 1))
		{
			var->on = 0;
			menu_button_in_game(var, pl);
		}
		if (var->menu_is_act == 2)
		{
			change_key(var, pl);
			choose_key(var, pl);
		}
	}
}
