/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:52:57 by serraoui          #+#    #+#             */
/*   Updated: 2023/12/02 21:09:50 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
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
	static char	*rest;
	char		*ret;
	ssize_t		r;

	r = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	while (1)
	{
		r = read_buffer(&rest, fd);
		if (ft_strchr(rest, '\n'))
			return (get_line__c(&rest));
		if (r < BUFFER_SIZE)
		{
			ret = ft_strdup(rest);
			free(rest);
			rest = NULL;
			return (ret);
		}
	}
	return (NULL);
}
