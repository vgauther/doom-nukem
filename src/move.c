/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:54:34 by vgauther          #+#    #+#             */
/*   Updated: 2020/01/08 15:24:02 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void end_of_level(t_var *var)
{
	if (var->player.pos.x >= var->maps[var->player.map].end_lv_x && var->maps[var->player.map].end_lv_x + 10 >= var->player.pos.x)
	{
		if (var->player.pos.y >= var->maps[var->player.map].end_lv_y && var->maps[var->player.map].end_lv_y + 10 >= var->player.pos.y)
		{
			if (var->m_count == var->player.map)
			{
				ft_putstr("fin du jeu\n");
			}
			else
			{
				ft_putstr("------ changement de map -------\n\n\n");

				var->player.map++;
				var->player.sector = var->maps[var->player.map].sectors[0];
				var->player.pos.x = var->maps[var->player.map].spawn_x;
				var->player.pos.y = var->maps[var->player.map].spawn_y;
			}
		}
	}
}
//
// void contact_wall(t_var *var, double save_x, double save_y)
// {
// 	double	a;
// 	double	b;
// 	double	wall_a;
// 	double	wall_b;
// 	double	x_a;
// 	double	x_b;
// 	double	y_a;
// 	double	y_b;
// 	int		n_map;
// 	int		n_sect;
// 	int		w;
// 	t_xy	i;
//
// 	n_map = var->player.map;
// 	n_sect = var->player.sector;
// 	printf("%d %d\n", n_map,n_sect);
// 	w = 0;
// 	//a = (save_y - var->player.pos.y) / (save_x - var->player.pos.x);
// 	// if ((save_x - var->player.pos.x) == 0)
// 	// {
// 	// 	a = 1;
// 	// }
// 	// else
// 	// {
// 		a = (save_y - var->player.pos.y) / (save_x - var->player.pos.x);
// 	// }
// 	b = save_y - a * save_x;
// 	printf("%s%f%s%f\n", "Test de colision\nPlayer Save :\n - x:",save_x, "\n- y:", save_y);
// 	printf("%s%f%s%f\n\n\n", "\nPlayer New :\n - x:",var->player.pos.x, "\n- y:", var->player.pos.y);
//
// 	while (w < var->sectors[var->maps[n_map].sectors[n_sect]].nb_pts - 1)
// 	{
// 		x_a = var->points[var->sectors[var->maps[n_map].sectors[n_sect]].pts[w]].x;
// 		x_b = var->points[var->sectors[var->maps[n_map].sectors[n_sect]].pts[w + 1]].x;
// 		y_a = var->points[var->sectors[var->maps[n_map].sectors[n_sect]].pts[w]].y;
// 		y_b = var->points[var->sectors[var->maps[n_map].sectors[n_sect]].pts[w + 1]].y;
// 		if ((x_b - x_a) == 0)
// 		{
// 			if ((save_x >= x_b && x_b <= var->player.pos.x) || (var->player.pos.x >= x_b && x_b <= save_x))
// 			{
// 				var->player.pos.x = save_x;
// 				var->player.pos.y = save_y;
// 				return ;
// 			}
// 		}
// 		else
// 		{
// 			wall_a = (y_b - y_a) / (x_b - x_a);
// 		}
// 		wall_b = y_a - wall_a * x_a;
// 		if (wall_a != a)
// 		{
// 			i.x = (b - wall_b) / (wall_a - a);
// 			i.y = a * i.x + b;
// 			// printf("%s%f%s%f\n", "\nPoint :\n - x:",x_a, "\n- y:", y_a);
// 			// printf("%s%f%s%f\n\n", "\nPoint :\n - x:",x_b, "\n- y:", y_b);
// 			// printf("inter :%f | %f\n", i.x, i.y);
// 			if ((var->player.pos.x >= i.x && i.x <= save_x) || (save_x >= i.x && i.x <= var->player.pos.x))
// 			{
// 				ft_putstr("\n\n--ok--\n\n");
// 				if ((var->player.pos.y >= i.y && i.y <= save_y) || (save_y >= i.y && i.y <= var->player.pos.y))
// 				{
// 					ft_putstr("contact - ");
// 					var->player.pos.x = save_x;
// 					var->player.pos.y = save_y;
// 					return ;
// 				}
// 			}
// 		}
//
// 		w++;
// 	}
// }

void move_forward(t_var *var, double i)
{
	double angle;
	double save_x;
	double save_y;

	save_x = var->player.pos.x;
	save_y = var->player.pos.y;
	angle = var->player.angle * RAD;
	if (cos(angle) != 0)
		var->player.pos.x = var->player.pos.x + cos(angle) * i;
	if (sin(angle) != 0)
		var->player.pos.y = var->player.pos.y + sin(angle) * i;
	contact_wall(var, save_x, save_y);
	end_of_level(var);
}

void move_backward(t_var *var)
{
	double angle;
	double save_x;
	double save_y;

	save_x = var->player.pos.x;
	save_y = var->player.pos.y;
	angle = var->player.angle * RAD;
	if (cos(angle) != 0)
		var->player.pos.x = var->player.pos.x - cos(angle) * 0.7;
	if (sin(angle) != 0)
		var->player.pos.y = var->player.pos.y - sin(angle) * 0.7;
	contact_wall(var, save_x, save_y);
	end_of_level(var);
}

void move_left(t_var *var)
{
	double angle;
	double save_x;
	double save_y;

	save_x = var->player.pos.x;
	save_y = var->player.pos.y;
	angle = (var->player.angle + 90) * RAD;
	if (cos(angle) != 0)
		var->player.pos.x = var->player.pos.x - cos(angle) * 1;
	if (sin(angle) != 0)
		var->player.pos.y = var->player.pos.y - sin(angle) * 1;
	contact_wall(var, save_x, save_y);
	end_of_level(var);
}

void move_right(t_var *var)
{
	double angle;
	double save_x;
	double save_y;

	save_x = var->player.pos.x;
	save_y = var->player.pos.y;
	angle = (var->player.angle - 90) * RAD;
	if (cos(angle) != 0)
		var->player.pos.x = var->player.pos.x - cos(angle) * 1.3;
	if (sin(angle) != 0)
		var->player.pos.y = var->player.pos.y - sin(angle) * 1.3;
	contact_wall(var, save_x, save_y);
	end_of_level(var);
}
