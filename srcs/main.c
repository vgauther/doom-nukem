/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:41:27 by ravernhe          #+#    #+#             */
/*   Updated: 2019/10/28 21:33:40 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include <pthread.h>

void		ft_clean_quit(SDL_Renderer *render, SDL_Window *window)
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(render);
	SDL_RenderPresent(render);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void	ft_init_sdl(t_var *var)
{
	var->sdl.window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return ;
	var->sdl.window = SDL_CreateWindow("WOLFCRAFT", SDL_WINDOWPOS_CENTERED, \
			SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, 0);
	var->sdl.render = SDL_CreateRenderer(var->sdl.window, -1, 0);
	if (!var->sdl.window || !var->sdl.render)
		return ;
}

void	init_key_move(t_var *var)
{
	var->key.left = SDLK_a;
	var->key.right = SDLK_d;
	var->key.forw = SDLK_w;
	var->key.back = SDLK_s;
	var->select_key = 0;
	var->key_id[0] = 3;
	var->key_id[1] = 0;
	var->key_id[2] = 22;
	var->key_id[3] = 18;
}

void *thread_1(void *arg)
{
	int x;
	int y;
	t_var *var;

	var = (t_var *)arg;
	x = 0;
	y = 100;

	while (x < 100)
	{
		y = 0;
		while (y < SIZE_Y)
		{
			SDL_SetRenderDrawColor(var->sdl.render, 0, 0, 255, 255);
			SDL_RenderDrawPoint(var->sdl.render, x, y);
			y++;
		}
		x++;
	}
	pthread_exit(NULL);
}

int		main(int ac, char **av)
{
	t_var			var;
	int x;
	int y;
	pthread_t thread1;

	x = 100;
	y = 0;
	ft_init_sdl(&var);
	if(pthread_create(&thread1, NULL, thread_1, (void *)&var) == -1)
	{
		perror("pthread_create");
		return EXIT_FAILURE;
	}
	if (pthread_join(thread1, NULL))
	{
		perror("pthread_join");
		return EXIT_FAILURE;
	}
	while (x < SIZE_X)
	{
		y = 0;
		while (y < SIZE_Y)
		{
			SDL_SetRenderDrawColor(var.sdl.render, 0, 200, 0, 255);
			SDL_RenderDrawPoint(var.sdl.render, x, y);
			y++;
		}
		x++;

	}
	SDL_RenderPresent(var.sdl.render);
	while (SDL_WaitEvent(&var.sdl.event))
	{
		if (var.sdl.event.type == SDL_QUIT)
			ft_clean_quit(var.sdl.render, var.sdl.window);
		else if (var.sdl.event.key.keysym.sym == SDLK_ESCAPE)
			ft_clean_quit(var.sdl.render, var.sdl.window);
	}
	(void)ac;
	(void)av;
	return (0);
}
