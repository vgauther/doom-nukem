/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tool_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 17:18:45 by ravernhe          #+#    #+#             */
/*   Updated: 2019/10/16 12:57:45 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	intersec_1(t_pos *a, t_var *var, t_player *player, double alpha)
{
	double xa;
	double ya;

	a->y = sin(alpha) > 0 ? (int)(player->pos.y / BSD) * BSD :
	(int)(player->pos.y / BSD) * BSD + BSD;
	xa = sin(alpha) > 0 ? 1.00 : -1.00;
	ya = sin(alpha) > 0 ? -BSD : BSD;
	a->x = (player->pos.y - a->y) / tan(alpha) + player->pos.x;
	xa *= BSD / tan(alpha);
	a->y = sin(alpha) > 0 ? a->y - 1 : a->y;
	while (a->y / BSD < var->y_max && a->x / BSD < var->x_max && a->y / BSD > 0
		&& a->x / BSD > 0 && (var->m[(int)(a->y / BSD)][(int)(a->x / BSD)] == 0
		|| var->m[(int)(a->y / BSD)][(int)(a->x / BSD)] == 7))
	{
		a->x += xa;
		a->y += ya;
	}
	a->y = sin(alpha) > 0 ? a->y + 1 : a->y + 0;
}

void	intersec_2(t_pos *b, t_var *var, t_player *player, double alpha)
{
	double xa;
	double ya;

	b->x = cos(alpha) > 0 ? (int)(player->pos.x / BSD) * BSD + BSD : \
			(int)(player->pos.x / BSD) * BSD;
	xa = cos(alpha) > 0 ? BSD : -BSD;
	ya = cos(alpha) > 0 ? -1.00 : 1.00;
	b->y = player->pos.y + (player->pos.x - b->x) * tan(alpha);
	ya *= BSD * tan(alpha);
	b->x = cos(alpha) > 0 ? b->x : b->x - 1;
	while (b->y / BSD < var->y_max && b->x / BSD < var->x_max && b->y / BSD > 0
		&& b->x / BSD > 0 && (var->m[(int)(b->y / BSD)][(int)(b->x / BSD)] == 0
		|| var->m[(int)(b->y / BSD)][(int)(b->x / BSD)] == 7))
	{
		b->x += xa;
		b->y += ya;
	}
	b->x = cos(alpha) > 0 ? b->x : b->x + 1;
}

void	calc_dist(double *dist, t_player *player, t_pos a, t_pos b)
{
	double f1;
	double f2;

	f1 = player->pos.x - a.x;
	f2 = player->pos.y - a.y;
	dist[0] = sqrt((f1 * f1) + (f2 * f2));
	f1 = player->pos.x - b.x;
	f2 = player->pos.y - b.y;
	dist[1] = sqrt((f1 * f1) + (f2 * f2));
}

int		launch_ray(t_player *player, t_var *var, double alpha, double beta)
{
	double		dist[2];
	t_pos		a;
	t_pos		b;

	init_a_b_alpha(&a, &b, &alpha);
	if (sin(alpha))
		intersec_1(&a, var, player, alpha);
	if (cos(alpha))
		intersec_2(&b, var, player, alpha);
	calc_dist(dist, player, a, b);
	if (dist[0] >= 0 && dist[1] >= 0)
	{
		if (dist[0] > dist[1])
			return (dist[1] * dist_0_1(var, alpha, beta, b));
		else
			return (dist[0] * dist_1_0(var, alpha, beta, a));
	}
	else if (dist[0] >= 0)
		return (dist[0] * dist_1_0(var, alpha, beta, a));
	return (dist[1] * dist_0_1(var, alpha, beta, b));
}
