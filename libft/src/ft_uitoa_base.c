/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:55:39 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/30 00:00:29 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_bzero1(char *s1, char *s2)
{
	int i;

	i = 0;
	while (i < 100)
	{
		s1[i] = '\0';
		s2[i] = '\0';
		i++;
	}
}

char		*rev_str(char *str, char *tmp, int j)
{
	int i;

	i = 0;
	while (j >= 0)
	{
		str[i] = tmp[j];
		j--;
		i++;
	}
	return (str);
}

char		*ft_uitoa_base(unsigned int n, int base)
{
	char	*str;
	int		j;
	char	*tmp;
	char	*dbase;

	if (base <= 1)
		return (0);
	str = (char*)malloc(sizeof(char) * 100);
	tmp = (char*)malloc(sizeof(char) * 100);
	if (str == NULL || tmp == NULL)
		return (NULL);
	dbase = "0123456789ABCDEF";
	ft_bzero1(str, tmp);
	j = 0;
	while (n > 0)
	{
		tmp[j] = dbase[n % base];
		n = n / base;
		j++;
	}
	j--;
	str = rev_str(str, tmp, j);
	free(tmp);
	return (str);
}
