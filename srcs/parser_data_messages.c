/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data_messages.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:56:40 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/17 12:21:33 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void parser_data_messages(int id)
{
	if (id == 0)
		ft_putstr("DATA PARSING ERROR : file not found.\n");
	else if (id == 1)
		ft_putstr("DATA PARSING ERROR : someone change the file name. The good file name is `data.emrv`.\n");
	else if (id == 1)
		ft_putstr("DATA PARSING ERROR : Ther is an unexpected char in data.emrv.\n");
}
