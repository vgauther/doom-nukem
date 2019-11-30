/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max_clamp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 22:42:52 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/30 22:44:52 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	max(double a, double b)
{
	return (a < b ? b : a);
}

double	min(double a, double b)
{
	return (a > b ? b : a);
}

int		clamp(int a, int b, int c)
{
	return (min(max(a, b), c));
}
