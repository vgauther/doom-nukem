/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:53:51 by ravernhe          #+#    #+#             */
/*   Updated: 2019/10/02 14:22:35 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static void	init_var(t_var *var)
{
	var->x_max = 0;
	var->y_max = 0;
	var->map = NULL;
}

static int	check_char(char *buff)
{
	int i;

	i = 0;
	if (!(buff[i]))
		return (1);
	while (buff[i])
	{
		if (buff[i] == WALL || buff[i] == COUL || buff[i] == ' ' ||\
			buff[i] == '\n' || buff[i] == SPAWN)
			i++;
		else
			return (1);
	}
	return (0);
}

void		parsing_map(int fd, t_var *var)
{
	char	*buff;
	char	*str;
	int		ret;
	int		token;
	size_t	nb_char;

	token = 0;
	init_var(var);
	if (!(str = ft_strnew(0)))
		ft_error(2);
	while ((ret = get_next_line(fd, &buff)))
	{
		if (token == 0 && (token = 1))
			nb_char = ft_strlen(buff);
		if (nb_char != ft_strlen(buff))
			ft_error(1);
		if (check_char(buff) == 1)
			ft_error(1);
		if (!(str = ft_strjoin_free_s1s2_newline(str, buff)))
			ft_error(2);
		var->y_max += 1;
	}
	check_map(var, ret, nb_char, str);
}
