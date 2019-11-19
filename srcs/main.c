/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 17:07:16 by math             ###   ########.fr       */
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
	var->points = malloc(sizeof(t_point) * 14);


	var->points[0].x = 0;
	var->points[0].y = 0;

	var->points[1].x = 250;
	var->points[1].y = 0;

	var->points[2].x = 250;
	var->points[2].y = 250;

	var->points[3].x = 150;
	var->points[3].y = 250;

	var->points[4].x = 100;
	var->points[4].y = 250;

	var->points[5].x = 0;
	var->points[5].y = 250;

	var->points[6].x = 0;
	var->points[6].y = 0;

	var->points[7].x = 0;
	var->points[7].y = 250;

	var->points[8].x = 100;
	var->points[8].y = 250;

	var->points[9].x = 150;
	var->points[9].y = 250;

	var->points[10].x = 250;
	var->points[10].y = 250;

	var->points[11].x = 250;
	var->points[11].y = 500;

	var->points[12].x = 0;
	var->points[12].y = 500;

	var->points[13].x = 0;
	var->points[13].y = 250;

	var->sectors = malloc(sizeof(t_sector) * 2);

	var->sectors[0].pts = malloc(sizeof(int) * 7);
	var->sectors[1].pts = malloc(sizeof(int) * 7);

	var->sectors[0].pts[0] = 0;
	var->sectors[0].pts[1] = 1;
	var->sectors[0].pts[2] = 2;
	var->sectors[0].pts[3] = 3;
	var->sectors[0].pts[4] = 4;
	var->sectors[0].pts[5] = 5;
	var->sectors[0].pts[6] = 6;
	var->sectors[0].floor = 0;
	var->sectors[0].ceilling = 30;


	var->sectors[1].pts[0] = 7;
	var->sectors[1].pts[1] = 8;
	var->sectors[1].pts[2] = 9;
	var->sectors[1].pts[3] = 10;
	var->sectors[1].pts[4] = 11;
	var->sectors[1].pts[5] = 12;
	var->sectors[1].pts[6] = 13;
	var->sectors[1].floor = 0;
	var->sectors[1].ceilling = 30;

	var->map[0].sectors = malloc(sizeof(int) * 2);

	var->map[0].sectors[0] = 0;
	var->map[0].sectors[1] = 1;
}

int		main(void)
{
	t_var			var;

	ft_init_sdl(&var);
	init_player(&var);
//	parser_data_main(&var);
	init_map(&var);
	display(&var);
	return (0);
}
