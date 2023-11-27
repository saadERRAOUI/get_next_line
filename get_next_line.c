/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:52:57 by serraoui          #+#    #+#             */
/*   Updated: 2023/11/26 22:16:43 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFF_SIZE 100000

//Todo : loop on the read s[BUFF_SIZE] from the file 
//! check if the return i of the read is not eqaul to -1 --> ERROR!
//Todo : do not loop on the read
//Todo : split code into situations 
//Todo : -- BUFFER_SIZE == Read - Line without '\n'
//Todo : -- BUFFER_SIZE == Read - Line with '\n'
//Todo : -- BUFFER_SIZE  > Read - Line with '\n'

// char	*get_next_line(int fd)
// {
// 	static char *rest;
// 	char		read_buffer[BUFF_SIZE + 1];
// 	char		*ret;
// 	size_t		i;

// 	if (fd < 0)
// 		return (NULL);
// 	if (rest) {
// 		//printf("### [%i][%s]%%\n", counter, rest);
// 		ret = ft_strdup(rest);
// 		free(rest);
// 	}
// 	else 
// 	{
// 		ret = (char *)malloc((1) * sizeof(char));
// 		if (!ret)
// 			return (NULL);
// 		ret[0] = '\0';
// 	}
// 	while (read(fd, read_buffer, BUFF_SIZE) > 0) 
// 	{
// 		i = 0;
// 		read_buffer[ft_strlen(read_buffer)] = 0;
// 		//printf("%zu ----- %s\n", ft_strlen(read_buffer), read_buffer);
// 		while (read_buffer[i])
// 		{
// 			if (read_buffer[i] == '\n') 
// 			{
// 				//printf("=== [%i][%s]%%\n", counter, read_buffer + (i + 1));
// 				rest = ft_strdup(read_buffer + (i + 1));
// 				//printf("=== [%i][%s]%%\n", counter++, rest);
// 				char* tmp2 = ft_substr(read_buffer, 0, i);
// 				char* tmp1 = ft_strjoin(ret, tmp2);
// 				free(ret);
// 				free(tmp2);
// 				return tmp1;
// 			}
// 			i++;
// 		}
// 		char *tmp = ft_strjoin(ret, read_buffer);
// 		free(ret);
// 		ret = tmp;
// 		// todo: free ret;
// 	}
// 	//free(read_buffer);
// 	return (ret);
// }

char *get_line(char *read, char *init_ret, char **rest)
{
	char	*ret;
	char	*tmp;
	int		i;
	
	i = 0;
	if (ft_strchr((*rest), '\n'))
	{
		while ((*rest)[i] != '\n')	
			i++;
		ret = ft_substr((*rest), 0, i);
		(*rest) = ft_strdup(read + (i + 1));
	}
	while (read[i] != '\n')	
		i++;
	tmp = ft_substr(read, 0, i);
	ret = ft_strjoin(init_ret, tmp);
	(*rest) = ft_strdup(read + (i + 1));
	//printf("$$---- [%s]\n", (*rest));
	free(tmp);
	return (ret);
}

char *init_ret(char **rest)
{
	char	*ret, *tmp;
	int 	i = 0;
	
	if ((*rest))
	{
		if (ft_strchr((*rest), '\n'))
		{
			while ((*rest)[i] != '\n')	
				i++;
			//printf("\n### ---- [%s]\n", ret);
			ret = ft_substr((*rest), 0, i);
			//printf("\n%%%% ---- [%s]\n", ret);
			tmp = *rest;
			(*rest) =  ft_strdup(*(rest) + (i + 1));
			//printf("\n### ---- [%s]\n", (*rest));
			free(tmp);
		}
		else
		{
			ret = ft_strdup((*rest));
			free(*rest);
			(*rest) = NULL;
		}
	}
	else
	{
		ret = (char *)malloc(1);
		ret[0] = '\0';
	}
	return (ret);
}

char *get_next_line(int fd)
{
	static char *rest;
	char		*ret;
	char		read_buffer[BUFF_SIZE + 1];
	ssize_t		r;

	ret = init_ret(&rest);
	while(1)
	{
		r = read(fd, read_buffer, BUFF_SIZE);
		printf("%s\n", read_buffer);
		if (r == -1)
			return (NULL);
		else {
			if (ft_strchr(read_buffer, '\n') || r < BUFF_SIZE)
				return get_line(read_buffer, ret, &rest);
			else
				ret = ft_strjoin(ret, read_buffer);
		}
	}
}

int main() {
	int fd, i;
	char path[] = "./text.txt";
	fd = open(path, O_RDONLY);
	i = 0;
	while (i < 4)
	{
		//printf("%s%%\n", get_next_line(fd));
		get_next_line(fd);
		i++;
	}
	system("leaks a.out");
	return (0);
}
