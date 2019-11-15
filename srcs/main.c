/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/15 18:59:24 by vgauther         ###   ########.fr       */
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
		var->player.pos.y = 60;
		var->player.pos.z = 6;
		var->player.angle = 0 * RAD;
		var->player.pcos = cos(var->player.angle);
		var->player.psin = sin(var->player.angle);
}

int		main(void)
{
	t_var			var;

	ft_init_sdl(&var);
	init_player(&var);

	printf("%f\n%f\n", hfov, vfov);
	display(&var);
	return (0);
}
