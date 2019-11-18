/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_recup_data_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:52:24 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/18 12:12:57 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void 	set_ennemy(t_var *var, char **tmp5)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < var->data.maps[var->data.map_count].nb_ennemies)
	{
		var->data.maps[var->data.map_count].ennemies[i].type = ft_atoi(tmp5[i]);
		var->data.maps[var->data.map_count].ennemies[i].x = ft_atoi(tmp5[i + 1]);
		var->data.maps[var->data.map_count].ennemies[i].y = ft_atoi(tmp5[i + 2]);
		var->data.maps[var->data.map_count].ennemies[i].hp = var->data.ennemies[var->data.maps[var->data.map_count].ennemies[i].type].hp;
		var->data.maps[var->data.map_count].ennemies[i].xp = var->data.ennemies[var->data.maps[var->data.map_count].ennemies[i].type].xp;
		i += 3;
		j++;
	}
}

static void 	set_weapon(t_var *var, char **tmp6)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < var->data.maps[var->data.map_count].nb_weapons)
	{
		var->data.maps[var->data.map_count].weapons[i].type = ft_atoi(tmp6[i]);
		var->data.maps[var->data.map_count].weapons[i].x = ft_atoi(tmp6[i + 1]);
		var->data.maps[var->data.map_count].weapons[i].y = ft_atoi(tmp6[i + 2]);
		var->data.maps[var->data.map_count].weapons[i].capa = var->data.weapons[var->data.maps[var->data.map_count].weapons[i].type].capa;
		i += 3;
		j++;
	}
}

int 	recup_data_map(t_var *var, char *str)
{
	char **tmp;
	char **tmp2;
	char **tmp3;
	char **tmp4;
	char **tmp5;
	char **tmp6;
	int i;

	if ((tmp = ft_strsplit(str, '[')) == NULL)
		return (1);
	if ((tmp2 = ft_strsplit(tmp[0], ']')) == NULL)
		return (free_tab_char_with_ret_1(tmp));
	if ((tmp3 = ft_strsplit(tmp2[0], '|')) == NULL)
		return (free_2_tab_char_ret_1(tmp, tmp2));
	if ((tmp4 = ft_strsplit(tmp3[0], ',')) == NULL)
		return (free_2_tab_char_ret_1(tmp, tmp2));
	i = 1;
	while (tmp4[i])
		i++;
	if (!(var->data.maps[var->data.map_count].sectors = malloc(sizeof(int) * (i - 1))))
		return (1);
	i = 1;
	while (tmp4[i])
	{
		var->data.maps[var->data.map_count].sectors[i - 1] = ft_atoi(tmp4[i]);
		i++;
	}
	if ((i = ft_atoi(tmp3[1])) == 0)
	{
		var->data.maps[var->data.map_count].nb_ennemies = i;
		var->data.maps[var->data.map_count].ennemies = NULL;
	}
	else
	{
		var->data.maps[var->data.map_count].nb_ennemies = i;
		if ((var->data.maps[var->data.map_count].ennemies = malloc(sizeof(t_ennemy) * i)))
			return (malloc_error("recup_data_map"));
		if ((tmp5 = ft_strsplit(tmp3[2], ',')) == NULL)
			return (free_2_tab_char_ret_1(tmp, tmp2));
		set_ennemy(var, tmp5);
	}
	if ((i = ft_atoi(tmp3[3])) == 0)
	{
		var->data.maps[var->data.map_count].nb_weapons = i;
		var->data.maps[var->data.map_count].weapons = NULL;
	}
	else
	{
		var->data.maps[var->data.map_count].nb_weapons = i;
		if ((tmp6 = ft_strsplit(tmp3[4], ',')) == NULL)
			return (1);
		set_weapon(var, tmp6);
	}
	return (0);
}
