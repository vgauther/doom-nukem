/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 11:44:22 by mamisdra          #+#    #+#             */
/*   Updated: 2019/01/18 14:37:50 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_restring(const int fd, char **data)
{
	char *py;

	if ((py = ft_strdup(ft_strchr(data[fd], '\n') + 1)))
		free(data[fd]);
	else
		return (-1);
	if ((data[fd] = ft_strdup(py)))
		free(py);
	else
		return (-1);
	return (0);
}

static int	ft_redline(const int fd, char **data)
{
	int		ret;
	char	*buf;
	char	*tmp;

	if (BUFF_SIZE <= 0)
		return (0);
	if (!(buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(tmp = ft_strjoin(data[fd], buf)))
			return (0);
		free(data[fd]);
		if (!(data[fd] = ft_strdup(tmp)))
			return (0);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	if (ret < 0)
		return (0);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*data[OPEN_MAX];
	int			i;

	if (!(fd < 0) && (OPEN_MAX > fd) && !data[fd])
		data[fd] = ft_strnew(1);
	i = 0;
	if (fd < 0 || line == NULL || OPEN_MAX <= fd || \
		(ft_redline(fd, data) == 0))
		return (-1);
	if (data[fd][0] == '\0')
		return (0);
	while (data[fd][i] != '\n' && data[fd][i] != '\0')
		i++;
	if (data[fd][i] == '\0' && data[fd][i - 1] == '\n')
	{
		free(data[fd]);
		return (0);
	}
	if (!(*line = ft_strsub(data[fd], 0, i)))
		return (-1);
	if (data[fd][i] == '\0' && (data[fd][0] = '\0') == 0)
		return (1);
	if (ft_restring(fd, data) == -1)
		return (-1);
	return (1);
}
