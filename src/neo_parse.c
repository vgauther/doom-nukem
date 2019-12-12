/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:18:11 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/10 13:14:15 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void free_1_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_3_tab(char **tab, char **tab2, char **tab3)
{
	free_1_tab(tab);
	free_1_tab(tab2);
	free_1_tab(tab3);
}

int check_resume(char *str)
{
	int i;
	int coma;

	coma = 0;
	i = 0;
	if (str[i] != '[')
		return (1);
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (str[i + 1] != 0 && (str[i + 1] == ',' || str[i - 1] == ','))
				return (1);
			coma++;
		}
		else if (str[i] <= '0' && str[i] >= '9' && (str[i] != ',' || str[i] != ']' || str[i] != '['))
			return (1);
		i++;
	}
	if (coma != 5)
		return (1);
	return (0);

}

void fill_resume(t_var *var, char *str)
{
	char **tmp1;
	char **tmp2;
	char **tmp3;

	if (check_resume(str))
		exit(1);
	tmp1 = ft_strplit(str, '[');
	tmp2 = ft_strplit(tmp1[0], ']');
	tmp3 = ft_strplit(tmp2[0], ',');
	var->nb_pts = ft_atoi(tmp3[1]);
	var->nb_sectors = ft_atoi(tmp3[2]);
	var->nb_maps = ft_atoi(tmp3[3]);
	var->nb_weapons = ft_atoi(tmp3[4]);
	var->nb_ennemies = ft_atoi(tmp3[5]);
	var->nb_textures = ft_atoi(tmp3[5]);
	var->points = (t_point *)malloc(sizeof(t_point) * var->points);
	var->sectors = (t_sector *)malloc(sizeof(t_sector) * var->sectors);
	var->maps = (t_map *)malloc(sizeof(t_map) * var->maps);
	var->weapons = (t_weapon *)malloc(sizeof(t_weapon) * var->weapons);
	var->ennemies = (t_ennemy *)malloc(sizeof(t_ennemy) * var->ennemies);
	free_3_tab(tmp1, tmp2, tmp3);

}

int check_points(char *str)
{
	int i;
	int coma;

	coma = 0;
	i = 0;
	if (str[i] != '[')
		return (1);
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (str[i + 1] != 0 && (str[i + 1] == ',' || str[i - 1] == ','))
				return (1);
			coma++;
		}
		else if (str[i] <= '0' && str[i] >= '9' && (str[i] != ',' || str[i] != ']' || str[i] != '['))
			return (1);
		i++;
	}
	if (coma != 2)
		return (1);
	return (0);

}

void fill_points(t_var *var, char *str)
{
	char **tmp1;
	char **tmp2;
	char **tmp3;

	if (check_points(str))
		exit(1);
	tmp1 = ft_strplit(str, '[');
	tmp2 = ft_strplit(tmp1[0], ']');
	tmp3 = ft_strplit(tmp2[0], ',');
	var->points[var->p_count].x = ft_atoi(tmp3[1]);
	var->points[var->p_count].y = ft_atoi(tmp3[2]);
	var->p_count++;
	free_3_tab(tmp1, tmp2, tmp3);
}

int check_weapons(char *str)
{
	int i;
	int coma;

	coma = 0;
	i = 0;
	if (str[i] != '[')
		return (1);
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (str[i + 1] != 0 && (str[i + 1] == ',' || str[i - 1] == ','))
				return (1);
			coma++;
		}
		else if (str[i] <= '0' && str[i] >= '9' && (str[i] != ',' || str[i] != ']' || str[i] != '['))
			return (1);
		i++;
	}
	if (coma != 3)
		return (1);
	return (0);

}

void fill_weapons(t_var *var, char *str)
{
	char **tmp1;
	char **tmp2;
	char **tmp3;

	// if (check_weapons(str))
	// 	exit(1);
	tmp1 = ft_strplit(str, '[');
	tmp2 = ft_strplit(tmp1[0], ']');
	tmp3 = ft_strplit(tmp2[0], ',');
	var->weapons[var->w_count].x = 0;
	var->weapons[var->w_count].y = 0;
	var->weapons[var->w_count].name[0] = tmp3[1][0];
	var->weapons[var->w_count].name[1] = tmp3[1][1];
	var->weapons[var->w_count].name[2] = tmp3[1][2];
	var->weapons[var->w_count].name[3] = tmp3[1][3];
	var->weapons[var->w_count].name[4] = 0;
	var->weapons[var->w_count].maga = ft_atoi(tmp3[2]);
	var->weapons[var->w_count].ammo = ft_atoi(tmp3[3]);
	var->w_count++;
	free_3_tab(tmp1, tmp2, tmp3);
}

int check_ennemies(char *str)
{
	int i;
	int coma;

	coma = 0;
	i = 0;
	if (str[i] != '[')
		return (1);
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (str[i + 1] != 0 && (str[i + 1] == ',' || str[i - 1] == ','))
				return (1);
			coma++;
		}
		else if (str[i] <= '0' && str[i] >= '9' && (str[i] != ',' || str[i] != ']' || str[i] != '['))
			return (1);
		i++;
	}
	if (coma != 2)
		return (1);
	return (0);

}

void fill_ennemies(t_var *var, char *str)
{
	char **tmp1;
	char **tmp2;
	char **tmp3;

	// if (check_ennemies(str))
	// 	exit(1);
	tmp1 = ft_strplit(str, '[');
	tmp2 = ft_strplit(tmp1[0], ']');
	tmp3 = ft_strplit(tmp2[0], ',');
	var->ennemies[var->e_count].x = 0;
	var->ennemies[var->e_count].y = 0;
	var->ennemies[var->e_count].name[0] = tmp3[1][0];
	var->ennemies[var->e_count].name[1] = tmp3[1][1];
	var->ennemies[var->e_count].name[2] = tmp3[1][2];
	var->ennemies[var->e_count].name[3] = tmp3[1][3];
	var->ennemies[var->e_count].name[4] = 0;
	var->ennemies[var->e_count].hp = ft_atoi(tmp3[2]);
	var->ennemies[var->e_count].xp = ft_atoi(tmp3[3]);
	var->e_count++;
	free_3_tab(tmp1, tmp2, tmp3);
}

void fill_sectors(t_var *var, char *str)
{
	char **tmp1;
	char **tmp2;
	char **tmp3;
	char **tmp4;
	char **tmp5;
	char **tmp6;
	char **tmp7;

	tmp1 = ft_strplit(str, '[');
	tmp2 = ft_strplit(tmp1[0], ']');
	tmp3 = ft_strplit(tmp2[0], '|');

	tmp4 = ft_strplit(tmp3[0], ',');
	tmp5 = ft_strplit(tmp3[1], ',');
	tmp6 = ft_strplit(tmp3[2], ',');
	tmp7 = ft_strplit(tmp3[3], ',');
	int i = 2;
	var->sectors[var->s_count].nb_pts = ft_atoi(tmp4[1]);
	var->sectors[var->s_count].pts = (int *)malloc(sizeof(int) * var->nb_pts);
	var->sectors[var->s_count].neighbors = (int *)malloc(sizeof(int) * (var->nb_pts - 1));
	while (tmp4[i])
	{
		var->sectors[var->s_count].pts[i - 2] = ft_atoi(tmp4[i]);
		if (i - 2 < (var->nb_pts - 1))
		{
			var->sectors[var->s_count].neighbors[i - 2] = ft_atoi(tmp6[i - 2]);
			var->sectors[var->s_count].textures[i - 2] = ft_atoi(tmp7[i - 2]);
		}
		i++;
	}
	var->sectors[var->s_count].floor = ft_atoi(tmp5[0]);
	var->sectors[var->s_count].ceilling = ft_atoi(tmp5[1]);
	var->s_count++;

}

void fill_maps(t_var *var, char *str)
{
	char **tmp1;
	char **tmp2;
	char **tmp3;
	char **tmp4;
	char **tmp5;
	char **tmp6;
	char **tmp7;
	char **tmp8;

	tmp1 = ft_strplit(str, '[');
	tmp2 = ft_strplit(tmp1[0], ']');
	tmp3 = ft_strplit(tmp2[0], '|');
	tmp4 = ft_strplit(tmp3[0], ',');
	tmp5 = ft_strplit(tmp3[1], ',');
	tmp6 = ft_strplit(tmp3[2], ',');
	tmp7 = ft_strplit(tmp3[3], ',');
	tmp8 = ft_strplit(tmp3[4], ',');
	var->maps[var->m_count].nb_sectors = ft_atoi(tmp4[1]);
	var->maps[var->m_count].nb_ennemies = ft_atoi(tmp5[0]);
	var->maps[var->m_count].nb_weapons = ft_atoi(tmp6[0]);

	int i = 2;
	var->maps[var->m_count].sectors = (int *)malloc(sizeof(int) * var->maps[var->m_count].nb_sectors)
	while (i < var->maps[var->m_count].nb_sectors + 2)
	{
		var->maps[var->m_count].sectors[i - 2] = ft_atoi(tmp4[i]);
		i++;
	}
	i = 0;
	var->maps[var->m_count].ennemies = (int *)malloc(sizeof(int) * var->maps[var->m_count].nb_ennemies)

	while (i < var->maps[var->m_count].nb_ennemies)
	{
		var->maps[var->m_count].ennemies[i].x = ft_atoi(tmp4[i]);
		var->maps[var->m_count].ennemies[i].y = ft_atoi(tmp4[i]);

		i++;
	}
	var->maps[var->m_count].spawn_x = ft_atoi(tmp7[0]);
	var->maps[var->m_count].spawn_y = ft_atoi(tmp7[1]);
	var->maps[var->m_count].end_lv_x = ft_atoi(tmp8[0]);
	var->maps[var->m_count].end_lv_y = ft_atoi(tmp8[1]);
	var->m_count++;
}

void  init_count(t_var *var)
{
	var->p_count = 0;
	var->m_count = 0;
	var->s_count = 0;
	var->w_count = 0;
	var->e_count = 0;
}

void init_map(t_var *var)
{
	char	*buff;
	int		fd;
	int		ret;

	if ((fd = open("data.emrv", 0)) < 0)
			exit(1);
	init_count(var);
	while ((ret = get_next_line(fd, &buff)))
	{
		if (buff[0] != '\0' && (buff[0] != '#'))
		{
			if (buff[0] == '[' && buff[1] == 'r')
				fill_resume(var, buff);
			else if (buff[0] == '[' && buff[1] == 'p')
				fill_points(var, buff);
			else if (buff[0] == '[' && buff[1] == 'w')
				fill_weapons(var, buff);
			else if (buff[0] == '[' && buff[1] == 'e')
				fill_ennemies(var, buff);
			else if (buff[0] == '[' && buff[1] == 's')
				fill_sectors(var, buff);
			else if (buff[0] == '[' && buff[1] == 'm')
				fill_maps(var, buff);
		}
	free(buff);
	}
	close(fd);
}
