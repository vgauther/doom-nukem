/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <mamisdra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:44:08 by mamisdra          #+#    #+#             */
/*   Updated: 2019/05/21 16:48:55 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	test_base(const char c)
{
	int	nb;

	if (c >= '0' && c <= '9')
		nb = c - '0';
	else if (c >= 'a' && c <= 'z')
		nb = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		nb = c - 'A' + 10;
	else
		nb = -1;
	return (nb);
}

int	ft_atoi_base_i(const char *str, int str_base, int i)
{
	int	neg;
	int	nb;
	int	current;

	nb = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	neg = (str[i] == '-' ? 1 : 0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	current = test_base(str[i]);
	while (current >= 0 && current < str_base)
	{
		nb = nb * str_base + current;
		i++;
		current = test_base(str[i]);
	}
	return (neg ? -nb : nb);
}
