/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <mamisdra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:06:12 by mamisdra          #+#    #+#             */
/*   Updated: 2019/10/13 18:41:32 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

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

double	dist_0_1(t_var *var, double alpha, double beta, t_pos b)
{
	var->texture_id = cos(alpha) > 0 ? 0 : 1;
	var->i = (int)b.y % BS_INT;
	return (cos(beta * RAD));
}

double	dist_1_0(t_var *var, double alpha, double beta, t_pos a)
{
	var->texture_id = sin(alpha) > 0 ? 2 : 3;
	var->i = (int)a.x % BS_INT;
	return (cos(beta * RAD));
}

int change_texture_key(int nk)
{
	if (nk >= 'a' && nk <= 'z')
		return (nk - 'a');
	else if (nk >= '0' && nk <= '9')
		return (nk - '0' + 27);
	else if (nk == 1073741906)
	 	return (37);
	else if (nk == 1073741905)
	 	return (38);
	else if (nk == 1073741904)
		return (40);
	else if (nk == 1073741903)
		return (39);
	return (26);
}

void	reset_after_change_key(t_var *var, t_player *player)
{
	int			x_y[2];

	x_y[0] = var->sdl.event.button.x;
	x_y[1] = var->sdl.event.button.y;
	if (var->sdl.event.type == SDL_KEYDOWN && var->select_key != 0)
	{
		var->select_key = 0;
		var->on = 2;
		option_menu(x_y, var, player);
		SDL_RenderPresent(var->sdl.render);
	}
}

void	change_key(t_var *var, t_player *player)
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
	reset_after_change_key(var, player);
}

void	choose_key(t_var *var, t_player *player)
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
			option_menu(x_y, var, player);
			SDL_RenderPresent(var->sdl.render);
		}
	}
}
