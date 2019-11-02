/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/02 23:29:11 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		**fill_map_struct(t_var var)
{
	int		**map;
	int		x_x2_y[3];

	x_x2_y[2] = -1;
	if (!(map = malloc(sizeof(int *) * var.y_max)))
		ft_error(2);
	while (++x_x2_y[2] != var.y_max)
	{
		if (!(map[x_x2_y[2]] = malloc(sizeof(int) * var.x_max)))
			ft_error(2);
	}
	x_x2_y[2] = 0;
	while (x_x2_y[2] != var.y_max)
	{
		x_x2_y[0] = 0;
		x_x2_y[1] = 0;
		while (x_x2_y[0] <= (var.x_max * 2))
		{
			map[x_x2_y[2]][x_x2_y[1]] = var.map[x_x2_y[2]][x_x2_y[0]] - 48;
			x_x2_y[1] += 1;
			x_x2_y[0] += 2;
		}
		x_x2_y[2]++;
	}
	return (map);
}

void free_tab_char(char **tab)
{
	int j;

	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

void free_tab_int(int **tab, int hei)
{
	int j;

	j = 0;
	while (hei > j)
	{
		free(tab[j]);
		printf("%s\n", "tea");
		j++;
	}
	free(tab);
}

void free_texture_in_var(t_var *v)
{
	int i;

	i = 0;
	while (v->key_texture[i])
	{
		SDL_FreeSurface(v->key_texture[i]);
		i++;
	}
}

void quit_free(SDL_Renderer *render, SDL_Window *win, t_var *var, int free_who)
{
	free_tab_int(var->m, var->y_max);
	free_texture_in_var(var);
	free_tab_char(var->map);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(win);
	SDL_Quit();
	(void)free_who;
}

void	player_data_set(t_var *var)
{
	int x;
	int y;

	y = 0;
	while (y != var->y_max)
	{
		x = 0;
		while (x != var->x_max)
		{
			if (var->m[y][x] == 7)
			{
				var->spawn.x = BLOCK_SIZE * x + BLOCK_SIZE / 2;
				var->spawn.y = BLOCK_SIZE * y + BLOCK_SIZE / 2;
				var->player.pos.x = var->spawn.x;
				var->player.pos.y = var->spawn.y;
			}
			x++;
		}
		y++;
	}
	var->player.height = BLOCK_SIZE / 2;
	var->player.fov = 60;
	var->player.angle = 210;
}

void	ft_init_sdl(t_var *var)
{
	var->sdl.window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return ;
	var->sdl.window = SDL_CreateWindow("WOLFCRAFT", SDL_WINDOWPOS_CENTERED, \
			SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, 0);
	var->sdl.render = SDL_CreateRenderer(var->sdl.window, -1, 1);
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

void is_first_char_zero(char *str)
{
	int fd;
	int ret;
	char buff[2];

	fd = open(str, O_RDONLY);
	ret = read(fd, buff, 2);
	buff[ret] = 0;
	close(fd);
	if (buff[0] == 0)
		ft_error(44);
}

int		main(int ac, char **av)
{
	int				fd;
	t_var			var;

	if ((fd = open(av[1], O_RDONLY)) < 0 || ac != 2)
		ft_error(5);
	is_first_char_zero(av[1]);
	ft_init_sdl(&var);
	init_key_move(&var);
	parsing_map(fd, &var);
	var.m = fill_map_struct(var);
	player_data_set(&var);
	open_wall_texture(&var);
	open_img_opt_button(&var);
	display(&var);
	close(fd);
	return (0);
}
