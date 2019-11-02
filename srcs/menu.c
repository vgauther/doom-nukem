/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmoreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:53:53 by esmoreau          #+#    #+#             */
/*   Updated: 2019/10/14 14:53:57 by esmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	move_key_edit_button(t_var *var, int *x_y, int i, int pos_x)
{
	SDL_Rect r;

	r = create_sdl_rect(530, pos_x, 0, 0);
	if (var->select_key == i)
		put_image(var, "./assets/op/ask.bmp", r);
	else if (x_y[0] > 530 && x_y[0] < 709 && x_y[1] > pos_x &&
		x_y[1] < (pos_x + 50) && var->menu_is_act != 0)
	{
		if (var->on == 0 || var->select_key == i)
			put_image(var, "./assets/op/ask.bmp", r);
		else
			put_image(var, "./assets/op/mod_o.bmp", r);
	}
	else if (var->menu_is_act != 0)
		put_image_opt(var, var->key_id[i - 1], r);
}

void	move_key_edit(t_var *var, int *x_y)
{
	move_key_edit_button(var, x_y, 1, 160);
	move_key_edit_button(var, x_y, 2, 230);
	move_key_edit_button(var, x_y, 3, 300);
	move_key_edit_button(var, x_y, 4, 370);
}

void	option_menu(int *x_y, t_var *var, t_player *player)
{
	put_image(var, "./assets/dirt_bg.bmp", create_sdl_rect(0, 0, 0, 0));
	if (x_y[0] > 20 && x_y[0] < 199 && x_y[1] > 500 && x_y[1] < 550)
	{
		put_image(var, "./assets/done_o.bmp", create_sdl_rect(20, 500, 0, 0));
		if (var->on == 0)
		{
			var->menu_is_act = 0;
			sdl_clean_screen(var->sdl.render);
			print_button(x_y, var, player);
		}
	}
	else
		put_image(var, "./assets/done.bmp", create_sdl_rect(20, 500, 0, 0));
	if (x_y[0] > 230 && x_y[0] < 409 && x_y[1] > 500 && x_y[1] < 550 \
		&& var->menu_is_act != 0)
		put_image(var, "./assets/reset_o.bmp", create_sdl_rect(230, 500, 0, 0));
	else if (var->menu_is_act != 0)
		put_image(var, "./assets/reset.bmp", create_sdl_rect(230, 500, 0, 0));
	move_key_edit(var, x_y);
}

void	print_button(int *x_y, t_var *var, t_player *player)
{
	put_image(var, "./assets/main_menu.bmp", create_sdl_rect(0, 0, 0, 0));
	if (x_y[0] >= 180 && x_y[0] <= 780 && x_y[1] >= 260 && x_y[1] <= 310)
	{
		buttons_menu_play(var, 1);
		if (var->on == 0)
		{
			var->menu_is_act = 1;
			sdl_clean_screen(var->sdl.render);
			print_screen(var, player);
		}
	}
	else
		buttons_menu_play(var, 0);
	if (x_y[0] >= 180 && x_y[0] <= 780 && x_y[1] >= 320 && x_y[1] <= 370 &&
		var->menu_is_act == 0)
	{
		buttons_menu_options(var, 1);
		if (var->on == 0 && (var->menu_is_act = 2))
		{
			sdl_clean_screen(var->sdl.render);
			option_menu(x_y, var, player);
		}
	}
	else if (var->menu_is_act == 0)
		buttons_menu_options(var, 0);
}

void	ft_menu(t_var *var, t_player *player)
{
	int			x_y[2];

	x_y[0] = var->sdl.event.button.x;
	x_y[1] = var->sdl.event.button.y;
	if (var->menu_is_act == 0)
		print_button(x_y, var, player);
	if (var->menu_is_act == 2)
		option_menu(x_y, var, player);
	if (var->menu_is_act == 0 || var->menu_is_act == 2)
		SDL_RenderPresent(var->sdl.render);
}
