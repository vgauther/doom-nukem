/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:10:15 by mamisdra          #+#    #+#             */
/*   Updated: 2018/11/12 14:44:42 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	i = 0;
	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	if ((s1 == NULL && s2 == NULL) || n == 0)
		return (0);
	while (s11[i] == s22[i] && i <= n && s11 && s22)
	{
		i++;
		if (n == i || (s11 == '\0' && s22 == '\0'))
			return (0);
	}
	return (s11[i] - s22[i]);
}
