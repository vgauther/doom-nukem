/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:51:53 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/05 19:20:17 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/doom.h"

void	init_count(t_var *var)
{
	var->p_count = 0;
	var->w_count = 0;
	var->e_count = 0;
	var->s_count = 0;
	var->m_count = 0;
}

int		data_weapons(t_var *var, char *buff, int x)
{
	int s;
	int	i;
	int b;

	b = 0;
	i = 0;
	s = 0;
	if (buff[x + 1] == '.')
		return (x + 1);
	while (buff[x] != '|')
	{
		if (buff[x] == ',')
		{
			if (i % 3 == 0)
			{
				b = ft_atoi(buff + x + 1);
				var->maps[var->m_count].weapons[i / 3] = b;
			}
			if (i % 3 == 1)
				var->weapons[b].x = ft_atoi(buff + x + 1);
			if (i % 3 == 2)
				var->weapons[b].y = ft_atoi(buff + x + 1);
			i++;
		}
		x++;
	}
	return (x);
}

int		data_ennemies(t_var *var, char *buff, int x)
{
	int s;
	int	i;
	int b;

	b = 0;
	i = 0;
	s = 0;
	if (buff[x + 1] == '.')
		return (x + 1);
	while (buff[x] != ']')
	{
		if (buff[x] == ',')
		{
			if (i % 3 == 0)
			{
				b = ft_atoi(buff + x + 1);
				var->maps[var->m_count].ennemies[i / 3] = b;
			}
			if (i % 3 == 1)
				var->ennemies[b].x = ft_atoi(buff + x + 1);
			if (i % 3 == 2)
				var->ennemies[b].y = ft_atoi(buff + x + 1);
 			i++;
		}
		x++;
	}
	return (x);
}

void	fill_maps(t_var *var, char *buff)
{
	int s;
	int i;
	int x;

	i = 0;
	x = 3;
	if (!(var->maps[var->m_count].sectors = malloc(sizeof(int) * ft_atoi(buff + x))))
		exit(1);
	while (buff[x] != ',')
		x++;
	s = 0;
	while (buff[x] != '|')
	{
		if (buff[x] == ',')
		{
			var->maps[var->m_count].sectors[s] = ft_atoi(buff + x + 1);
			s++;
		}
		x++;
	}
	x++;
	if (!(var->maps[var->m_count].weapons = malloc(sizeof(int) * ft_atoi(buff + x))))
		exit(1);
	var->maps[var->m_count].nb_weapons = ft_atoi(buff + x);
	while (buff[x] != ',')
		x++;
	x = data_weapons(var, buff, x);
	x++;
	if (!(var->maps[var->m_count].ennemies = malloc(sizeof(int) * ft_atoi(buff + x))))
		exit(1);
	var->maps[var->m_count].nb_ennemies = ft_atoi(buff + x);
	while (buff[x] != ',')
		x++;
	x = data_ennemies(var, buff, x);
	var->m_count += 1;
}

void	fill_resume(t_var *var, char *buff)
{
	int	x;

	x = 3;
	if (!(var->points = malloc(sizeof(t_point) * ft_atoi(buff + x))))
		exit(1);
	while (buff[x] != ',')
		x++;
	if (!(var->sectors = malloc(sizeof(t_sector) * ft_atoi(buff + x))))
		exit(1);
	while (buff[x] != ',')
		x++;
	/*if (!(var->nb_textures = malloc(sizeof(t_texture * ft_atoi(buff + x)))))
		return (ft_error(2));
	while (buff[x] != ',')
		x++;*/
	if (!(var->maps = malloc(sizeof(t_map) * ft_atoi(buff + x))))
		exit(1);
	while (buff[x] != ',')
		x++;
	if (!(var->weapons = malloc(sizeof(t_weapon) * ft_atoi(buff + x))))
		exit(1);
	while (buff[x] != ',')
		x++;
	if (!(var->ennemies = malloc(sizeof(t_ennemy) * ft_atoi(buff + x))))
		exit(1);
}

void	fill_data_struct(t_var *var)
{
	char	*buff;
	int		fd;
	int		ret;

	init_count(var);
	if ((fd = open("data.emrv", O_RDONLY)) < 0)
	 		return ;
	while ((ret = get_next_line(fd, &buff)))
	{
		if (buff[0] != '#')
		{
			if (buff[1] == 'r')
				fill_resume(var, buff);
			else if (buff[1] == 'p')
				fill_points(var, buff);
			else if (buff[1] == 'w')
				fill_weapons(var, buff);
			else if (buff[1] == 'e')
				fill_ennemies(var, buff);
			else if (buff[1] == 's')
				fill_sectors(var, buff);
			else if (buff[1] == 'm')
				fill_maps(var, buff);
		}
	}
	close(fd);
}
