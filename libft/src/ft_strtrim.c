/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:55:39 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/30 00:00:15 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_none(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (c);
	return (0);
}

char			*ft_strtrim(const char *s)
{
	char		*str;
	int			i;
	size_t		l;

	l = 0;
	if (s != NULL)
	{
		while (ft_none(*s) != 0)
			s++;
		while (s[l] != '\0')
		{
			i = 0;
			while (ft_none(s[i + l]) != 0)
				i++;
			if (i > 0 && s[i + l] == '\0')
				break ;
			else if (i > 0)
				l = l + i;
			l++;
		}
		str = ft_strnew(l);
		ft_memcpy(str, s, l);
		return (str);
	}
	return (NULL);
}
