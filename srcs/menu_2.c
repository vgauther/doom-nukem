/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmoreau <esmoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:54:11 by esmoreau          #+#    #+#             */
/*   Updated: 2019/11/02 23:29:17 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	buttons_menu_options(t_var *var, int i)
{
	SDL_Rect r;

	r = create_sdl_rect(180, 320, 0, 0);
	if (i == 0)
		put_image(var, "./assets/options.bmp", r);
	else
		put_image(var, "./assets/options_press.bmp", r);
}

void	buttons_menu_play(t_var *var, int i)
{
	SDL_Rect r;

	r = create_sdl_rect(180, 260, 0, 0);
	if (i == 0)
		put_image(var, "./assets/jouer.bmp", r);
	else
		put_image(var, "./assets/jouer_press.bmp", r);
}

void	reset_after_change_key(t_var *var)
{
	int			x_y[2];

	x_y[0] = var->sdl.event.button.x;
	x_y[1] = var->sdl.event.button.y;
	if (var->sdl.event.type == SDL_KEYDOWN && var->select_key != 0)
	{
		var->select_key = 0;
		var->on = 2;
		option_menu(x_y, var);
		SDL_RenderPresent(var->sdl.render);
	}
}

void	change_key(t_var *var)
{
	if (var->select_key == 1 && var->sdl.event.type == SDL_KEYDOWN)
	{
		var->key.right = var->sdl.event.key.keysym.sym;
		var->key_id[0] = change_texture_key(var->sdl.event.key.keysym.sym);
	}
	else if (var->select_key == 2 && var->sdl.event.type == SDL_KEYDOWN)
	{
		var->key.left = var->sdl.event.key.keysym.sym;
		var->key_id[1] = change_texture_key(var->sdl.event.key.keysym.sym);
	}
	else if (var->select_key == 3 && var->sdl.event.type == SDL_KEYDOWN)
	{
		var->key.forw = var->sdl.event.key.keysym.sym;
		var->key_id[2] = change_texture_key(var->sdl.event.key.keysym.sym);
	}
	else if (var->select_key == 4 && var->sdl.event.type == SDL_KEYDOWN)
	{
		var->key.back = var->sdl.event.key.keysym.sym;
		var->key_id[3] = change_texture_key(var->sdl.event.key.keysym.sym);
	}
	reset_after_change_key(var);
}

void	choose_key(t_var *var)
{
	int			x_y[2];

	x_y[0] = var->sdl.event.button.x;
	x_y[1] = var->sdl.event.button.y;
	if (SDL_MOUSEBUTTONDOWN == var->sdl.event.type)
	{
		if (x_y[0] > 530 && x_y[0] < 709 && x_y[1] > 160 && x_y[1] < 210)
			var->select_key = 1;
		else if (x_y[0] > 530 && x_y[0] < 709 && x_y[1] > 230 && x_y[1] < 280)
			var->select_key = 2;
		else if (x_y[0] > 530 && x_y[0] < 709 && x_y[1] > 300 && x_y[1] < 350)
			var->select_key = 3;
		else if (x_y[0] > 530 && x_y[0] < 709 && x_y[1] > 370 && x_y[1] < 420)
			var->select_key = 4;
		else if (x_y[0] > 230 && x_y[0] < 409 && x_y[1] > 500 && x_y[1] < 550)
		{
			init_key_move(var);
			option_menu(x_y, var);
			SDL_RenderPresent(var->sdl.render);
		}
	}
}
