/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:10:40 by mamisdra          #+#    #+#             */
/*   Updated: 2018/11/13 16:30:30 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_src;
	size_t	size_dst;
	size_t	i;
	size_t	j;

	size_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	i = 0;
	j = 0;
	if (size == 0)
		return (size_src);
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && i + j < size - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	if (size_dst > size)
		return (size + size_src);
	if (size_dst <= size)
		return (size_src + size_dst);
	return (0);
}
