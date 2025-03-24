/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:07:54 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/03 23:29:37 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

static char	*ft_copy(char *str, char *str1)
{
	char	*str2;

	if (!str)
		str2 = ft_strjoin("", str1);
	else
	{
		str2 = ft_strjoin(str, str1);
		free(str);
	}
	return (str2);
}

static char	*ft_read(char *str, int fd)
{
	char	*str1;
	int		a;

	str1 = malloc(BUFFER_SIZE + 1);
	if (!str1)
		return (NULL);
	a = read(fd, str1, BUFFER_SIZE);
	while (a > 0)
	{
		str1[a] = '\0';
		str = ft_copy(str, str1);
		if (ft_strchr(str1, '\n'))
			break ;
		a = read(fd, str1, BUFFER_SIZE);
	}
	free(str1);
	if (a == -1)
	{
		free (str);
		return (NULL);
	}
	return (str);
}

static char	*ft_n(char *str)
{
	char	*str1;
	int		a;
	int		b;

	a = 0;
	b = 0;
	if (!str[a])
		return (NULL);
	while (str[b] != '\n' && str[b] != '\0')
		b++;
	str1 = malloc(sizeof(char) * (b + 2));
	if (!str1)
	{
		free (str1);
		return (NULL);
	}
	while (str[a] != '\n' && str[a] != '\0')
	{
		str1[a] = str[a];
		a++;
	}
	if (str[a] == '\n')
		str1[a++] = '\n';
	str1[a] = '\0';
	return (str1);
}

static char	*ft_checkpoint(char *str)
{
	char	*str1;
	int		a;
	int		b;
	int		c;

	a = 0;
	b = 0;
	c = ft_strlen(str);
	while (str[a] && str[a] != '\n')
		a++;
	if (str[a] == '\n')
		a++;
	str1 = malloc(c - a + 1);
	if (!str1)
		return (NULL);
	while (str[a])
	{
		str1[b] = str[a];
		a++;
		b++;
	}
	str1[b] = '\0';
	return (str1);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*str1;
	char		*str2;

	if (fd < 0 || BUFFER_SIZE < 1)
	{
		if (str)
			free(str);
		return (NULL);
	}
	str = ft_read(str, fd);
	if (!str)
		return (NULL);
	str1 = ft_n(str);
	if (!str1)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str2 = ft_checkpoint(str);
	free(str);
	str = str2;
	return (str1);
}
// int main(int argc,char **argv)
// {
// 	int a;
// 	int fd;
// 	char *str;

// 	a = 1;
// 	while (a < argc)
// 	{
// 		fd = open(argv[a], O_RDONLY);
// 		if (fd < 0)
// 			return (0);
// 		str = get_next_line(fd);
// 		while (str !=  0)
// 		{
// 			printf("%s", str);
// 			free(str);
// 			str = get_next_line(fd);
// 		}
// 		a++;
// 		close(fd);
// 	}
// 	return(0);
// }
