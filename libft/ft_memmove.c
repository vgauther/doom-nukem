/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:37:06 by mamisdra          #+#    #+#             */
/*   Updated: 2018/11/13 14:37:09 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*src2;
	char	*dest2;
	size_t	i;

	i = -1;
	src2 = (char *)src;
	dest2 = (char *)dest;
	if (src2 < dest2)
		while ((int)--n >= 0)
			*(dest2 + n) = *(src2 + n);
	else
		while (++i < n)
			*(dest2 + i) = *(src2 + i);
	return (dest);
}
