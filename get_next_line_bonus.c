/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:52:57 by serraoui          #+#    #+#             */
/*   Updated: 2023/12/02 21:38:21 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line__c(char **rest)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	while ((*rest)[i] != '\n')
		i++;
	ret = ft_substr((*rest), 0, i + 1);
	tmp = *rest;
	(*rest) = ft_strdup((*rest) + (i + 1));
	free(tmp);
	return (ret);
}

ssize_t	read_buffer(char **rest, int fd)
{
	char	*read_buff;
	ssize_t	r;

	read_buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buff)
		return (0);
	r = read(fd, read_buff, BUFFER_SIZE);
	if (r == -1)
	{
		free(*rest);
		free(read_buff);
		(*rest) = NULL;
		return (0);
	}
	read_buff[r] = '\0';
	(*rest) = ft_strjoin((*rest), read_buff);
	free(read_buff);
	return (r);
}

char	*get_next_line(int fd)
{
	static char	*rest[1024];
	char		*ret;
	ssize_t		r;

	r = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		r = read_buffer(&rest[fd], fd);
		if (ft_strchr(rest[fd], '\n'))
			return (get_line__c(&rest[fd]));
		if (r < BUFFER_SIZE)
		{
			ret = ft_strdup(rest[fd]);
			free(rest[fd]);
			rest[fd] = NULL;
			return (ret);
		}
	}
	return (NULL);
}
