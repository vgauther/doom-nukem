/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:34:03 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/14 20:55:36 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

double pythagore(double a, double b)
{
	return(sqrt(a * a + b + b));
}

float yaw(int x, int y, int player_yaw)
{
	return (x + y * player_yaw);
}

float max(float a, float b)
{
	return (a < b ? b : a);
}

float min(float a, float b)
{
	return (a > b ? b : a);
}

float clamp(int a, int b, int c)
{
	return (min(max(a, b), c));
}
