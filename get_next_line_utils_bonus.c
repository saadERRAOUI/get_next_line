/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:36:56 by serraoui          #+#    #+#             */
/*   Updated: 2023/11/29 20:37:04 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"


size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	if (!s1 || !ft_strlen(s1))
		return (NULL);
	dup = (char *) malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if(!s)
		return (NULL);
	if (ft_strlen(s) - start < (unsigned int)len)
		len = ft_strlen(s) - start;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s;

	if (!s1 && !s2)
		return (0);
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	while (s1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = 0;
	free ((void *)s1);
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	char	character;

	character = (char) c;
	if (!s)
		return (NULL);
	// if (character == '\0' && s)
	// 	return ((char *)(s + ft_strlen(s)));
	while (*s)
	{
		//printf("+++ s[%c] character[%c]\n", *s, character);
		if (*s == character)
			return ((char *)s);
		s++;
	}
	// if (character == '\0')
	// 	return ((char *)s);
	return (NULL);
}
