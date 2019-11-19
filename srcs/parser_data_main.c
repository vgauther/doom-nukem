/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:51:53 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 16:46:23 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/doom.h"
//
// /*
// ** check if the file can be open and exist
// */
//
// int is_the_file_a_good_file(char *name)
// {
// 	int fd;
// 
// 	if ((fd = open(name, O_RDONLY)) < 0)
// 		return (1);
// 	close(fd);
// 	return (0);
// }
//
// /*
// ** check if the name of the file is good
// */
//
// int is_a_good_name(char *name)
// {
// 	if (ft_strcmp(name, "data.emrv"))
// 		return (1);
// 	return (0);
// }
//
// /*
// ** check if the the char in param is printable abc or 123 char
// */
//
// int is_a_printable_char(char c)
// {
// 	if ((c >= 32 && c < 127) || c == 0)
// 		return (0);
// 	return (1);
// }
//
// int check_all_char(char *name)
// {
// 	int fd;
// 	int ret;
// 	int token;
// 	char *buff;
// 	int i;
// 	int j;
//
// 	token = 0;
// 	j = 0;
// 	i = 0;
// 	if ((fd = open(name, O_RDONLY)) < 0)
// 		return (1);
// 	while((ret = get_next_line(fd, &buff)))
// 	{
// 		if (token == 0)
// 		{
// 			token = 1;
// 			if (buff[0] == 0)
// 				return (1);
// 		}
// 		i = 0;
// 		while (buff[i])
// 		{
// 			if (is_a_printable_char(buff[i]))
// 				return (1);
// 			i++;
// 		}
// 		free(buff);
// 		j++;
// 	}
// 	close(fd);
// 	return (0);
// }
//
// int check_bracket_on_the_line(char *str)
// {
// 	int i;
//
// 	if (str)
// 	{
// 		i = ft_strlen(str);
// 		if (str[0] != '[' || str[i - 1] != ']' || str[i] != 0)
// 			return (1);
// 		return (0);
// 	}
// 	return (1);
// }
//
// int how_many_of_this_char(char *str, char c)
// {
// 	int i;
// 	int ret;
//
// 	i = 0;
//
// 	if (str)
// 	{
// 		ret = 0;
// 		while (str[i])
// 		{
// 			if (str[i] == c)
// 				ret++;
// 			i++;
// 		}
// 		return (ret);
// 	}
// 	return (-1);
// }
//
// int this_char_in_a_row(char *str, char c)
// {
// 	int i;
//
// 	i = 0;
// 	if (str)
// 	{
// 		while (str[i])
// 		{
// 			if (str[i] == c && str[i + 1] == c)
// 				return (1);
// 			i++;
// 		}
// 		return (0);
// 	}
// 	return (1);
// }
//
// int valid_char_for_settings_line(char *str)
// {
// 	int i;
//
// 	i = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] >= '0' && str[i] <= '9') || str[i] == ',')
// 			i++;
// 		else if (str[i] == '[' || str[i] == ']')
// 			i++;
// 		else
// 			return (1);
// 	}
// 	return (0);
// }
//
// int check_point_line(char *str)
// {
// 	if (str)
// 	{
// 		if (this_char_in_a_row(str, ','))
// 			return (1);
// 		return(0);
// 	}
// 	return (1);
// }
//
// int check_line_by_line(char *name)
// {
// 	int 	fd;
// 	int 	ret;
// 	char 	*buff;
// 	int 	j;
//
// 	j = 0;
// 	if ((fd = open(name, O_RDONLY)) < 0)
// 		return (1);
// 	while((ret = get_next_line(fd, &buff)))
// 	{
// 		if (j == 0)
// 		{
// 			if (ft_strcmp("# nb of point, nb of sector, nb of texture, nb of map, nb of weapon, nb of ennemies", buff))
// 				return (1);
//
// 		}
// 		else if (j == 2)
// 		{
// 			if (check_bracket_on_the_line(buff))
// 				return (1);
// 			if (how_many_of_this_char(buff, ',') != 3)
// 				return (1);
// 			if (this_char_in_a_row(buff, ','))
// 				return (1);
// 			if (valid_char_for_settings_line(buff))
// 				return (1);
//
// 		}
// 		else if (j == 2)
// 		{
// 			if (ft_strcmp("# p means point, coor x, coor y", buff))
// 				return (1);
// 		}
// 		else
// 		{
// 			if (buff[0] == '#')
// 			{
// 				ft_putstr("c un com");
// 			}
// 			else
// 			{
// 				if (check_bracket_on_the_line(buff))
// 					return (1);
// 				if (buff[1] == 'p')
// 				{
// 					if (check_point_line(buff))
// 						return (1);
// 				}
// 			}
// 		}
// 		free(buff);
// 		j++;
// 	}
// 	close(fd);
// 	return (0);
// }
//
// int check_file_data(char *name)
// {
// 	if (is_the_file_a_good_file(name))
// 	{
// 		parser_data_messages(0);
// 		return (1);
// 	}
// 	if (is_a_good_name(name))
// 	{
// 		parser_data_messages(1);
// 		return (1);
// 	}
// 	if (check_all_char(name))
// 	{
// 		parser_data_messages(2);
// 		return (1);
// 	}
// 	if (check_line_by_line(name))
// 	{
// 		parser_data_messages(2);
// 		return (1);
// 	}
// 	return (0);
// }
//
// int recup_settings(t_var *var, char *str)
// {
// 	char **tmp;
// 	char **tmp2;
// 	char **tmp3;
//
// 	if ((tmp = ft_strsplit(str, '[')) == NULL)
// 		return (1);
// 	if ((tmp2 = ft_strsplit(tmp[0], ']')) == NULL)
// 		return (1);
// 	if ((tmp3 = ft_strsplit(tmp2[0], ',')) == NULL)
// 		return (free_2_tab_char_ret_1(tmp, tmp2));
// 	var->data.nb_points = ft_atoi(tmp3[0]);
// 	var->data.nb_sectors = ft_atoi(tmp3[1]);
// 	var->data.nb_textures = ft_atoi(tmp3[2]);
// 	var->data.nb_maps = ft_atoi(tmp3[3]);
// 	free_3_tab_char(tmp, tmp2, tmp3);
// 	return (0);
// }
//
// int recup_data_point(t_var *var, char *str)
// {
// 	char **tmp;
// 	char **tmp2;
// 	char **tmp3;
//
// 	if ((tmp = ft_strsplit(str, '[')) == NULL)
// 		return (1);
// 	if ((tmp2 = ft_strsplit(tmp[0], ']')) == NULL)
// 	{
// 		free_tab_char(tmp);
// 		return (1);
// 	}
// 	if ((tmp3 = ft_strsplit(tmp2[0], ',')) == NULL)
// 	{
// 		free_2_tab_char(tmp, tmp2);
// 		return (1);
// 	}
// 	var->data.points[var->data.point_count].x = ft_atoi(tmp3[1]);
// 	var->data.points[var->data.point_count].y = ft_atoi(tmp3[2]);
// 	free_3_tab_char(tmp, tmp2, tmp3);
// 	return (0);
// }
//
// int recup_data_sector(t_var *var, char *str)
// {
// 	char **tmp;
// 	char **tmp2;
// 	char **tmp3;
// 	char **tmp4;
// 	char **tmp5;
// 	int i;
//
// 	if ((tmp = ft_strsplit(str, '[')) == NULL)
// 		return (1);
// 	if ((tmp2 = ft_strsplit(tmp[0], ']')) == NULL)
// 		return (free_tab_char_with_ret_1(tmp));
// 	if ((tmp3 = ft_strsplit(tmp2[0], '|')) == NULL)
// 		return (free_2_tab_char_ret_1(tmp, tmp2));
// 	if ((tmp4 = ft_strsplit(tmp3[1], ',')) == NULL)
// 		return (free_3_tab_char_ret_1(tmp, tmp2, tmp3));
// 	if ((tmp5 = ft_strsplit(tmp3[0], ',')) == NULL)
// 		return (free_4_tab_char_ret_1(tmp, tmp2, tmp3, tmp4));
// 	var->data.sectors[var->data.sector_count].floor = ft_atoi(tmp4[0]);
// 	var->data.sectors[var->data.sector_count].ceilling = ft_atoi(tmp4[1]);
// 	i = 3;
// 	while (tmp5[i])
// 		i++;
// 	if (!(var->data.sectors[var->data.sector_count].pts = malloc(sizeof(int) * i)))
// 		return (malloc_error("recup_data_sector"));
// 	i = 1;
// 	while (tmp5[i])
// 	{
// 		var->data.sectors[var->data.sector_count].pts[i - 1] = ft_atoi(tmp5[i]);
// 		i++;
// 	}
// 	return (0);
// }
//
// int recup_data_weapon(t_var *var, char *str)
// {
// 	(void)var;
// 	(void)str;
// 	return (0);
// }
//
// int recup_data_ennemy(t_var *var, char *str)
// {
// 	char **tmp;
// 	char **tmp2;
// 	char **tmp3;
//
// 	if ((tmp = ft_strsplit(str, '[')) == NULL)
// 		return (1);
// 	if ((tmp2 = ft_strsplit(tmp[0], ']')) == NULL)
// 		return (free_tab_char_with_ret_1(tmp));
// 	if ((tmp3 = ft_strsplit(tmp2[0], ',')) == NULL)
// 		return (free_2_tab_char_ret_1(tmp, tmp2));
// 	return (0);
// 	(void)var;
// }
// int recup_data(t_var *var, char *name)
// {
// 	int 	fd;
// 	int 	i;
// 	char 	*buff;
// 	int 	ret;
// 	i = 0;
// 	if ((fd = open(name, O_RDONLY)) < 0)
// 		return (1);
// 	while ((ret = get_next_line(fd, &buff)))
// 	{
// 		if (i == 1)
// 		{
// 			if ((recup_settings(var, buff)))
// 				return (1);
// 			if(!(var->data.points = malloc(sizeof(t_point) * var->data.nb_points)))
// 				return (1);
// 			if(!(var->data.sectors = malloc(sizeof(t_sector) * var->data.nb_sectors)))
// 				return (1);
// 			if(!(var->data.maps = malloc(sizeof(t_map) * var->data.nb_maps)))
// 				return (1);
// 			if(!(var->data.weapons = malloc(sizeof(t_weapon) * var->data.nb_weapons)))
// 				return (1);
// 		}
// 		else if (i > 2)
// 		{
// 			if (buff[0] != '#')
// 			{
// 				if (buff[1] == 'p')
// 				{
// 					recup_data_point(var, buff);
// 					var->data.point_count++;
// 				}
// 				else if (buff[1] == 's')
// 				{
// 					recup_data_sector(var, buff);
// 					var->data.sector_count++;
// 				}
// 				else if (buff[1] == 'm')
// 				{
// 					recup_data_map(var, buff);
// 					var->data.map_count++;
// 				}
// 				else if (buff[1] == 'e')
// 				{
// 					recup_data_ennemy(var, buff);
// 					var->data.ennemy_count++;
// 				}
// 				else if (buff[1] == 'w')
// 				{
// 					recup_data_weapon(var, buff);
// 					var->data.weapon_count++;
// 				}
// 			}
// 		}
// 		i++;
// 		free(buff);
// 	}
// 	close(fd);
// 	return (0);
// }
//
// int parser_data_main(t_var *var)
// {
// 	char *name;
//
// 	if ((name = ft_strdup("data.emrv")) == NULL)
// 		return (1);
// 	if (check_file_data(name))
// 		return (free_ret_1(name));
// 	var->data.point_count = 0;
// 	var->data.sector_count = 0;
// 	var->data.map_count = 0;
// 	if (recup_data(var, name))
// 		return (free_ret_1(name));
// 	free(name);
// 	(void)var;
// 	return (0);
// }
