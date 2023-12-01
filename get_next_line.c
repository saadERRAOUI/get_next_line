/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:52:57 by serraoui          #+#    #+#             */
/*   Updated: 2023/11/29 21:52:11 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Todo : loop on the read s[BUFFER_SIZE] from the file 
//! check if the return i of the read is not eqaul to -1 --> ERROR!
//Todo : do not loop on the read
//Todo : split code into situations 
//Todo : -- BUFFER_SIZE == Read - Line without '\n'
//Todo : -- BUFFER_SIZE == Read - Line with '\n'
//Todo : -- BUFFER_SIZE  > Read - Line with '\n'

char *get_line__c(char **rest)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	while ((*rest)[i] != '\n')
		i++;
	//printf("=Before=[%s][%zu]%%\n", (*rest), ft_strlen((*rest)));
	ret = ft_substr((*rest), 0, i + 1);
	tmp = *rest;
	(*rest) = ft_strdup((*rest) + (i + 1));
	//printf("=After=[%s][%zu]%%\n", (*rest), ft_strlen((*rest)));
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

ssize_t read_buffer(char **rest, int fd)
{
	char	read_buff[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t		r;

	r = read(fd, read_buff, BUFFER_SIZE);
	if (r == -1)
	{
		free(*rest);
		(*rest) = NULL;
		return (0);
	}
	// ** ft_strjoin frees the rest before returning the new one;
	read_buff[r] = '\0';
	temp = ft_strjoin((*rest), read_buff);
	if (temp) {
		(*rest) = temp;
		//free(temp);
	}
	else {
		(*rest) = NULL;
		return (-1);
	}
	return (r);
}

char *get_next_line(int fd)
{
	static char *rest;
	char		*ret;
	ssize_t		r;

	r = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while(1)
	{
		r = read_buffer(&rest, fd);
		//printf("[%zi]\n", r);
		if (r == -1)
			return (NULL);
		if (ft_strchr(rest, '\n'))
			return get_line__c(&rest);
		if (r < BUFFER_SIZE)
		{
			//printf("REST[%s]\n", rest);
			ret = ft_strdup(rest);
			//printf("REST[%s]\n", ret);
			free(rest);
			rest = NULL;
			return (ret);
		}
	}
	return(NULL);
}
/*
int main() {
	int fd, i, fd1;
	char path[] = "./text.txt";
	fd = open(path, O_RDONLY);
	printf("[%i]\n", fd);
	char path2[] = "./test2.txt";
	fd1 = open(path2, O_RDONLY);
	printf("[%i]\n", fd1);
	i = 0;
	printf("%s%%\n", get_next_line(fd));
	printf("*************************************\n");
	printf("%s%%\n", get_next_line(fd1));
	printf("*************************************\n");
	printf("%s%%\n", get_next_line(fd));
	printf("*************************************\n");
	printf("%s%%\n", get_next_line(fd1));
	//printf("%s%%\n", get_next_line(fd));
	system("leaks a.out");
	close(fd);
	close(fd1);
	return (0);
}

int main() {
	int fd, i, fd1;
	char path[] = "./test_empty.text";
	fd = open(path, O_RDONLY);
	printf("[%i]==>%s%%\n", fd, get_next_line(fd));
	system("leaks a.out");
	close(fd);
	return (0);
}*/