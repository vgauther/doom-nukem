/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:57:37 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/17 14:58:29 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void forward(t_var *var, double speed, double angle)
{
	angle = angle * RAD;
	if (cos(angle) != 0)
		var->player.pos.x += speed * cos(angle);
	if (sin(angle) != 0)
		var->player.pos.y += speed * sin(angle);
}

void	backward(t_var *var, double speed, double angle)
{
	angle = angle * RAD;
	if (cos(angle) != 0)
		var->player.pos.x -= speed * cos(angle);
	if (sin(angle) != 0)
		var->player.pos.y -= 1 * (speed * sin(angle));
}
