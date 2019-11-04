/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/02 23:29:22 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	fill_red(t_var *var)
{
	int x;
	int y;

	SDL_SetRenderDrawColor(var->sdl.render, 0, 0, 93, 0);
	y = 0;
	while (y < SIZE_Y)
	{
		x = 0;
		while (x < SIZE_X)
		{
			SDL_RenderDrawPoint(var->sdl.render, x, y);
			x++;
		}
		y++;
	}
	SDL_RenderPresent(var->sdl.render);
}

void	display(t_var *var)
{
	while (SDL_WaitEvent(&var->sdl.event))
	{
		if (var->sdl.event.type == SDL_QUIT)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.key.keysym.sym == SDLK_ESCAPE)
			ft_clean_quit(var->sdl.render, var->sdl.window);
		else if (var->sdl.event.key.keysym.sym == SDLK_p)
			fill_red(var);
	}
}
