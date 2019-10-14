/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <mamisdra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:19:41 by mamisdra          #+#    #+#             */
/*   Updated: 2019/10/03 15:03:35 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static void	put_wall_around_the_map(int hei, int len, t_var *var)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (var->map[0][x])
	{
		if (var->map[0][x] == SPAWN || var->map[hei - 1][x] == SPAWN)
			ft_error(6);
		var->map[0][x] = WALL;
		var->map[hei - 1][x] = WALL;
		x++;
	}
	while (y < hei)
	{
		if (var->map[y][0] == SPAWN || var->map[y][len * 2] == SPAWN)
			ft_error(6);
		var->map[y][0] = WALL;
		var->map[y][len * 2] = WALL;
		y++;
	}
}

static int	check_spawn(char *str)
{
	int i;
	int spawn;

	i = 0;
	spawn = 0;
	while (str[i])
	{
		if (str[i] == SPAWN)
			spawn++;
		i++;
	}
	if (spawn == 1)
		return (0);
	if (spawn > 1 || spawn == 0)
		return (1);
	return (0);
}

static int	check_space_between_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i % 2 != 0)
		{
			if (str[i] != ' ' && str[i] != '\n')
				return (1);
		}
		else
		{
			if (str[i] == ' ' || str[i] == '\n')
				return (1);
		}
		i++;
	}
	return (0);
}

void		check_map(t_var *var, int ret, size_t nb_char, char *str)
{
	if (ret == -1 || var->y_max == 0)
		ft_error(-1);
	if (check_spawn(str) == 1)
		ft_error(3);
	if (check_space_between_digit(str) == 1)
		ft_error(1);
	var->x_max = nb_char / 2;
	if (!(var->map = split(str, '\n')))
		ft_error(2);
	put_wall_around_the_map(var->y_max, var->x_max, var);
	free(str);
}
