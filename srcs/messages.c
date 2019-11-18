/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:31:08 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/18 11:34:00 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int malloc_error(char *str)
{
	ft_putstr("MALLOC ERROR : a malloc failed in the function ");
	ft_putstr(str);
	ft_putstr(".\n");
	return (1);
}
