/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:54:34 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/06 12:04:18 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void move_forward(t_var *var, double i)
{
	double angle;

	angle = var->player.angle * RAD;
	if (cos(angle) != 0)
	{
		var->player.pos.x = var->player.pos.x + cos(angle) * i;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y + sin(angle) * i;
	}
}

void move_backward(t_var *var)
{
	double angle;

	angle = var->player.angle * RAD;
	if (cos(angle) != 0)
	{
		var->player.pos.x = var->player.pos.x - cos(angle) * 1;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y - sin(angle) * 1;
	}
}

void move_left(t_var *var)
{
	double angle;

	angle = (var->player.angle + 90) * RAD;
	if (cos(angle) != 0)
	{
		var->player.pos.x = var->player.pos.x - cos(angle) * 1;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y - sin(angle) * 1;
	}
}

void move_right(t_var *var)
{
	double angle;

	angle = (var->player.angle - 90) * RAD;
	if (cos(angle) != 0)
	{
		var->player.pos.x = var->player.pos.x - cos(angle) * 1;
	}
	if (sin(angle) != 0)
	{
		var->player.pos.y = var->player.pos.y - sin(angle) * 1;
	}
}
