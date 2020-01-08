/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vcp_yaw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:22:44 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/13 14:24:35 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double yaw(double a, double b, double c)
{
	return (a + b * c);
}

double v_c_p(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - x2 * y1);
}
