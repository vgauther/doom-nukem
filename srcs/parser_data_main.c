/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:51:53 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/17 13:35:24 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int is_the_file_a_good_file(char *name)
{
	int fd;

	if ((fd = open(name, O_RDONLY)) < 0)
		return (1);
	close(fd);
	return (0);
}

int is_a_good_name(char *name)
{
	if (ft_strcmp(name, "data.emrv"))
		return (1);
	return (0);
}

int is_a_printable_char(char c)
{
	if ((c >= 32 && c <= 127) || c == 0)
		return (0);
	return (1);
}

int check_all_char(char *name)
{
	int fd;
	int ret;
	int token;
	char *buff;
	int i;
	int j;

	token = 0;
	j = 0;
	i = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		return (1);
	while((ret = get_next_line(fd, &buff)))
	{
		if (token == 0)
		{
			token = 1;
			if (buff[0] == 0)
				return (1);
		}
		i = 0;
		while (buff[i])
		{
			if (is_a_printable_char(buff[i]))
				return (1);
			i++;
		}
		free(buff);
		j++;
	}
	close(fd);
	return (0);
}

int check_bracket_on_the_line(char *str)
{
	int i;

	if (str)
	{
		i = ft_strlen(str);
		if (str[0] != '[' || str[i - 1] != ']' || str[i] != 0)
			return (1);
		return (0);
	}
	return (1);
}

int how_many_of_this_char(char *str, char c)
{
	int i;
	int ret;

	i = 0;

	if (str)
	{
		ret = 0;
		while (str[i])
		{
			if (str[i] == c)
				ret++;
			i++;
		}
		return (ret);
	}
	return (-1);
}

int this_char_in_a_row(char *str, char c)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == c && str[i + 1] == c)
			{
				return (1);
			}
			i++;
		}
		return (0);
	}
	return (1);
}

int valid_char_for_settings_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == ',' || str[i] == '[' || str[i] == ']')
			i++;
		else
			return (1);
	}
	return (0);
}

int check_point_line(char *str)
{
	if (str)
	{
		return(0);
	}
	return (1);
}

int check_line_by_line(char *name)
{
	int fd;
	int ret;
	char *buff;
	int j;

	j = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		return (1);
	while((ret = get_next_line(fd, &buff)))
	{
		if (j == 0)
		{
			if (ft_strcmp("# nb of point, nb of sector, nb of texture, nb of map", buff))
				return (1);

		}
		else if (j == 2)
		{
			if (check_bracket_on_the_line(buff))
				return (1);
			if (how_many_of_this_char(buff, ',') != 3)
				return (1);
			if (this_char_in_a_row(buff, ','))
				return (1);
			if (valid_char_for_settings_line(buff))
				return (1);

		}
		else if (j == 2)
		{
			if (ft_strcmp("# p means point, coor x, coor y", buff))
				return (1);
		}
		else
		{
			if (buff[0] == '#')
			{
				ft_putstr("c un com");
			}
			else
			{
				if (check_bracket_on_the_line(buff))
					return (1);
				if (buff[1] == 'p')
				{
					if (check_point_line(buff))
						return (1);
				}
			}
		}
		free(buff);
		j++;
	}
	close(fd);
	return (0);
}

int parser_data_main(t_var *var)
{
	char *name;

	name = ft_strdup("data.emrv");
	if (is_the_file_a_good_file(name))
	{
		parser_data_messages(0);
		free(name);
		return (1);
	}
	if (is_a_good_name(name))
	{
		parser_data_messages(1);
		free(name);
		return (1);
	}
	if (check_all_char(name))
	{
		parser_data_messages(2);
		free(name);
		return (1);
	}
	if (check_line_by_line(name))
	{
		parser_data_messages(2);
		free(name);
		return (1);
	}
	free(name);
	(void)var;
	return (0);
}
