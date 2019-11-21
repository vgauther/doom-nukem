/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:51:53 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/21 22:16:33 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	fill_points(t_var *var, char *buff)
{
	int x;

	x = 3;
	var->points[var->p_count].x = ft_atoi(buff + x);
	while (buff[x] != ',')
		x++;
	var->points[var->p_count].y = ft_atoi(buff + x + 1);
	var->p_count += 1;
}

/* Mettre le nom des armes avec 4 char dans le fichier emrv*/
void	fill_weapons(t_var *var, char *buff)
{
	int 	x;
	int 	w;

	x = 3;
	w = 0;
	while (w < 4)
	{
		var->weapons[var->w_count].name[w] = buff[x];
		w++;
		x++;
	}
	var->weapons[var->w_count].name[4] = '\0';
	var->weapons[var->w_count].maga = ft_atoi(buff + x + 1);
	x++;
	while (buff[x] != ',')
		x++;
	var->weapons[var->w_count].ammo = ft_atoi(buff + x + 1);
	var->w_count += 1;
}

void	fill_ennemies(t_var *var, char *buff)
{
	int 	x;
	int 	w;

	x = 3;
	w = 0;
	while (w < 4)
	{
		var->ennemies[var->e_count].name[w] = buff[x];
		w++;
		x++;
	}
	var->ennemies[var->e_count].name[4] = '\0';
	var->ennemies[var->e_count].hp = ft_atoi(buff + x + 1);
	x++;
	while (buff[x] != ',')
		x++;
	var->ennemies[var->e_count].xp = ft_atoi(buff + x + 1);
	var->e_count += 1;
}

void	fill_sectors(t_var *var, char *buff)
{
	int	i;
	int	x;

	x = 3;
	var->sectors[var->s_count].nb_pts = (unsigned int)ft_atoi(buff + x);
	if (!(var->sectors[var->s_count].pts = malloc(sizeof(int) * ft_atoi(buff + x))))
		return (ft_error(2));
	while (buff[x] != ',')
		x++;
	i = 0;
	while (buff[x] != '|')
	{
		if (buff[x] == ',')
		{
			x++;
			var->sectors[var->s_count].pts[i] = ft_atoi(buff + x);
			i++;
		}
		x++;
	}
	var->sectors[var->s_count].floor = ft_atoi(buff + x + 1);
	while (buff[x] != ',')
		x++;
	var->sectors[var->s_count].ceilling = ft_atoi(buff + x + 1);
	var->s_count += 1;
}
