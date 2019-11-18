/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:33:52 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/17 19:43:29 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int free_ret_1(char *str)
{
	free(str);
	return (1);
}

int free_2_str(char *str)
{
	free(str);
	return (1);
}

int free_2_tab_char_ret_1(char **tab, char **tab1)
{
	free_tab_char(tab);
	free_tab_char(tab1);
	return (1);
}

int free_3_tab_char_ret_1(char **tab, char **tab1, char **tab2)
{
	free_tab_char(tab);
	free_tab_char(tab1);
	free_tab_char(tab2);
	return (1);
}

int free_4_tab_char_ret_1(char **tab, char **tab1, char **tab2, char **tab3)
{
	free_tab_char(tab);
	free_tab_char(tab1);
	free_tab_char(tab2);
	free_tab_char(tab3);
	return (1);
}
