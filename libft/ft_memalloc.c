/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:09:53 by mamisdra          #+#    #+#             */
/*   Updated: 2018/11/12 13:09:56 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memalloc(size_t size)
{
	char	*alloc;
	size_t	i;

	i = 0;
	if (!(alloc = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	while (i < size)
	{
		alloc[i] = '\0';
		i++;
	}
	return (alloc);
}
