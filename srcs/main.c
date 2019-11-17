/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/17 12:07:24 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_init_sdl(t_var *var)
{
	var->sdl.window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return ;
	var->sdl.window = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, \
			SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, 0);
	var->sdl.render = SDL_CreateRenderer(var->sdl.window, -1, 1);
	if (!var->sdl.window || !var->sdl.render)
		return ;
}
void init_player(t_var *var)
{
		var->player.pos.x = 50;
		var->player.pos.y = 50;
		var->player.pos.z = 6;
		var->player.angle = 0;
		var->player.pcos = cos(var->player.angle * RAD);
		var->player.psin = sin(var->player.angle * RAD);
}

void init_map(t_var *var)
{
		var->map[0].x = 0;
		var->map[0].y = 0;

		var->map[1].x = 80;
		var->map[1].y = 0;

		var->map[2].x = 100;
		var->map[2].y = 20;

		var->map[3].x = 100;
		var->map[3].y = 100;

		var->map[4].x = 0;
		var->map[4].y = 100;

		var->map[5].x = 0;
		var->map[5].y = 0;
}

int		main(void)
{
	t_var			var;

	ft_init_sdl(&var);
	init_player(&var);
	parser_data_main(&var);
	init_map(&var);
	display(&var);
	return (0);
}
