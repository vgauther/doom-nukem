/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:54:34 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/08 22:10:40 by vgauther         ###   ########.fr       */
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
int change_sector(t_var *var, int old_sect, int new_sect)
{
	int old_floor;
	int new_floor;
	int new_ceilling;

	old_floor = var->sectors[old_sect].floor;
	new_floor = var->sectors[new_sect].floor;
	new_ceilling = var->sectors[new_sect].ceilling;

	if (new_ceilling - new_floor < 10)
		return (1);
	if ((old_floor - new_floor) <= -3 || (old_floor - new_floor) >= 3)
		return (1);
	var->player.sector = new_sect;
	var->player.pos.z = var->player.pos.z + ((old_floor - new_floor) * -1);
	ft_putstr("changement de secteur\n");
	return (0);

}

void contact_wall(t_var *var, double save_x, double save_y)
{
	double new_x;
	double new_y;
	int map;
	int sector;
	int w;

	double xa;
	double xb;
	double ya;
	double yb;
	w = 0;
	new_x = var->player.pos.x;
	new_y = var->player.pos.y;
	map = var->player.map;
	sector = var->player.sector;
	while (w < var->sectors[sector].nb_pts)
	{
		xa = var->points[var->sectors[sector].pts[w]].x;
		xb = var->points[var->sectors[sector].pts[w + 1]].x;

		ya = var->points[var->sectors[sector].pts[w]].y;
		yb = var->points[var->sectors[sector].pts[w + 1]].y;
		// if (new_x == save_x)
		// {
		//
		// }
		/*else*/ if (xa == xb)
		{
		//	printf("%f|%f\n", var->player.pos.x, var->player.pos.y);
		//	printf("%f\n", xa);
			if ((save_x >= xa && xa >= new_x) || (new_x >= xa && xa >= save_x))
			{
				ft_putstr("CONTACT\n");
				if (var->sectors[sector].neighbors[w] != -1)
				{
					ft_putstr("bjr voisin");
					if (change_sector(var, sector, var->sectors[sector].neighbors[w]) == 0)
						return ;
				}
				var->player.pos.x = save_x;
				var->player.pos.y = save_y;
				return ;
			}
		}
		if (ya == yb)
		{
			if ((save_y >= ya && ya >= new_y) || (new_y >= ya && ya >= save_y))
			{
				if ((xa >= save_x && save_x >= xb) || (xb >= save_x && save_x >= xa))
				{
					ft_putstr("CONTACT\n");
					if (var->sectors[sector].neighbors[w] != -1)
					{
						ft_putstr("bjr voisin");
						if (change_sector(var, sector, var->sectors[sector].neighbors[w]) == 0)
							return ;
					}
					var->player.pos.x = save_x;
					var->player.pos.y = save_y;
					return ;
				}
			}
		}
		//
		// double ya;
		// double yb;
		//
		// xa = var->sectors[sector].pts[w]

		w++;
	}
}

void move_forward(t_var *var, double i)
{
	double angle;
	double save_x;
	double save_y;

	save_x = var->player.pos.x;
	save_y = var->player.pos.y;
	angle = var->player.angle * RAD;
	if (cos(angle) != 0)
	{
		var->player.pos.x = var->player.pos.x + cos(angle) * i;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y + sin(angle) * i;
	}
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
	{
		var->player.pos.x = var->player.pos.x - cos(angle) * 0.5;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y - sin(angle) * 0.5;
	}
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
	{
		var->player.pos.x = var->player.pos.x - cos(angle) * 1;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y - sin(angle) * 1;
	}
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
	{
		var->player.pos.x = var->player.pos.x - cos(angle) * 1;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y - sin(angle) * 1;
	}
	contact_wall(var, save_x, save_y);
	end_of_level(var);
}
