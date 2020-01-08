/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:39:18 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/15 13:32:41 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
/*
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
	return (0);

}

int contact_x(t_var *var, double xa, double xb, double save_x, double save_y, int sector, int w, int new_x)
{
	if (xa == xb)
	{
		if ((save_x >= xa && xa >= new_x) || (new_x >= xa && xa >= save_x))
		{
			if (var->sectors[sector].neighbors[w] != -1)
			{
				if (change_sector(var, sector, var->sectors[sector].neighbors[w]) == 0)
					return (1);
			}
			var->player.pos.x = save_x;
			var->player.pos.y = save_y;
			return (1);
		}
	}
	return (0);
}

int contact_y(t_var *var, double xa, double xb, double ya, double yb,double save_x, double save_y, int sector, int w, int new_y)
{
	if (ya == yb)
	{
		if ((save_y >= ya && ya >= new_y) || (new_y >= ya && ya >= save_y))
		{
			if ((xa >= save_x && save_x >= xb) || (xb >= save_x && save_x >= xa))
			{
				if (var->sectors[sector].neighbors[w] != -1)
				{
					if (change_sector(var, sector, var->sectors[sector].neighbors[w]) == 0)
						return (1);
				}
				var->player.pos.x = save_x;
				var->player.pos.y = save_y;
				return (1);
			}
		}
	}
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
	while (w < var->sectors[sector].nb_pts - 1)
	{
		xa = var->points[var->sectors[sector].pts[w]].x;
		xb = var->points[var->sectors[sector].pts[w + 1]].x;
		ya = var->points[var->sectors[sector].pts[w]].y;
		yb = var->points[var->sectors[sector].pts[w + 1]].y;
		if (contact_x(var, xa, xb, save_x, save_y, sector, w, new_x))
			return ;
		if (contact_y(var, xa, xb, ya, yb, save_x, save_y, sector, w, new_x))
			return ;
		w++;
	}
}
*/
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
	ft_putstr("nouveau secteur :");
	ft_putnbr(var->player.sector);
	ft_putstr("\n");

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
	while (w < var->sectors[sector].nb_pts - 1)
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
