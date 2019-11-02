/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/02 23:14:13 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static int	col(int **map, double x, double y)
{
	if (map[(int)(y / BLOCK_SIZE)][(int)(x / BLOCK_SIZE)] == 1)
		return (0);
	return (1);
}

static void	forward(t_player *pl, double angle, int speed, int **map)
{
	angle = (angle - 30) * RAD;
	if (cos(angle) > 0)
	{
		if (col(map, pl->pos.x + (speed * fabs(cos(angle))), pl->pos.y))
			pl->pos.x += speed * fabs(cos(angle));
	}
	else if (cos(angle) < 0)
	{
		if (col(map, pl->pos.x + (-1 * (speed * fabs(cos(angle)))), pl->pos.y))
			pl->pos.x += -1 * (speed * fabs(cos(angle)));
	}
	if (sin(angle) > 0)
	{
		if (col(map, pl->pos.x, pl->pos.y + (-1 * (speed * fabs(sin(angle))))))
			pl->pos.y += -1 * (speed * fabs(sin(angle)));
	}
	else if (sin(angle) < 0)
	{
		if (col(map, pl->pos.x, pl->pos.y + (speed * fabs(sin(angle)))))
			pl->pos.y += speed * fabs(sin(angle));
	}
}

static void	backward(t_player *pl, double angle, int speed, int **map)
{
	angle = (angle - 30) * RAD;
	if (cos(angle) > 0)
	{
		if (col(map, pl->pos.x - (speed * fabs(cos(angle))), pl->pos.y))
			pl->pos.x -= speed * fabs(cos(angle));
	}
	else if (cos(angle) < 0)
	{
		if (col(map, pl->pos.x - (-1 * (speed * fabs(cos(angle)))), pl->pos.y))
			pl->pos.x -= -1 * (speed * fabs(cos(angle)));
	}
	if (sin(angle) > 0)
	{
		if (col(map, pl->pos.x, pl->pos.y - (-1 * (speed * fabs(sin(angle))))))
			pl->pos.y -= -1 * (speed * fabs(sin(angle)));
	}
	else if (sin(angle) < 0)
	{
		if (col(map, pl->pos.x, pl->pos.y - (speed * fabs(sin(angle)))))
			pl->pos.y -= speed * fabs(sin(angle));
	}
}

void		ft_move(int key, SDL_Renderer *render, t_var *var)
{
	if (key == var->key.forw)
		forward(&var->player, var->player.angle, 25, var->m);
	else if (key == var->key.back)
		backward(&var->player, var->player.angle, 25, var->m);
	else if (key == var->key.left)
		var->player.angle += DIV_60_SIZE * 75.00;
	else if (key == var->key.right)
		var->player.angle -= DIV_60_SIZE * 75.00;
	sdl_clean_screen(render);
	print_screen(var);
}
