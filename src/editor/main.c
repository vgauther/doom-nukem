/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 22:35:30 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/01 22:37:35 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	ft_putstr("Nom de la map créée :");
	ft_putstr(av[1]);
	return 0;
}