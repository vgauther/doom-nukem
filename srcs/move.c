/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <mamisdra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:30:53 by mamisdra          #+#    #+#             */
/*   Updated: 2019/10/16 12:57:18 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

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

void		ft_move(int key, t_player *player, SDL_Renderer *render, t_var *var)
{
	if (key == var->key.forw)
		forward(player, player->angle, 25, var->m);
	else if (key == var->key.back)
		backward(player, player->angle, 25, var->m);
	else if (key == var->key.left)
		player->angle += DIV_60_SIZE * 75.00;
	else if (key == var->key.right)
		player->angle -= DIV_60_SIZE * 75.00;
	sdl_clean_screen(render);
	print_screen(var, player);
}
