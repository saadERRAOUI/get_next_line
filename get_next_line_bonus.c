/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:53:21 by serraoui          #+#    #+#             */
/*   Updated: 2023/12/01 16:12:57 by serraoui         ###   ########.fr       */
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
	char		read_buff[BUFFER_SIZE + 1];
	ssize_t		r;

	r = read(fd, read_buff, BUFFER_SIZE);
	if (r == -1)
	{
		free(*rest);
		(*rest) = NULL;
		return (0);
	}
	// ** ft_strjoin frees the rest before returning the new one;
	if (!r)
		read_buff[r] = '\0';
	(*rest) = ft_strjoin((*rest), read_buff);
	//printf("TEST-REST[%s]\n", (*rest));
	return (r);
}

char	*get_next_line(int fd)
{
	static char *rest[1024];
	char 		*ret;
	ssize_t		r;
	
	while(1)
	{
		// printf("[%s]\n", rest[fd]);
		r = read_buffer(&rest[fd], fd);
		if (ft_strchr(rest[fd], '\n'))
			return get_line__c(&rest[fd]);
		if (r < BUFFER_SIZE)
		{
			//printf("REST[%s]\n", rest[fd]);
			ret = ft_strdup(rest[fd]);
			//printf("REST[%s]\n", ret);
			free(rest[fd]);
			rest[fd] = NULL;
			return (ret);
		}
	}
	return (NULL);
}


// int main() {
// 	int fd, i, fd1;
// 	char path[] = "./test_empty.text";
// 	fd = open(path, O_RDONLY);
// 	printf("[%i]==>%s%%\n", fd, get_next_line(fd));
// 	system("leaks a.out");
// 	close(fd);
// 	return (0);
// }