/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/17 15:35:42 by vgauther         ###   ########.fr       */
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
		var->player.pos.z = 9;
		var->player.angle = 0;
		var->player.pcos = cos(var->player.angle * RAD);
		var->player.psin = sin(var->player.angle * RAD);
}

void init_map(t_var *var)
{
		var->map[0].x = 0;
		var->map[0].y = 0;

		var->map[1].x = 300;
		var->map[1].y = 0;

		var->map[2].x = 300;
		var->map[2].y = 300;

		var->map[3].x = 175;
		var->map[3].y = 300;

		var->map[4].x = 175;
		var->map[4].y = 400;

		var->map[5].x = 300;
		var->map[5].y = 400;

		var->map[6].x = 300;
		var->map[6].y = 700;

		var->map[7].x = 0;
		var->map[7].y = 700;

		var->map[8].x = 0;
		var->map[8].y = 400;

		var->map[9].x = 125;
		var->map[9].y = 400;

		var->map[10].x = 125;
		var->map[10].y = 300;

		var->map[11].x = 0;
		var->map[11].y = 300;

		var->map[12].x = 0;
		var->map[12].y = 0;

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
