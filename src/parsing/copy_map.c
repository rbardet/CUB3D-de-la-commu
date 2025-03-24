/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 02:20:17 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/20 08:52:03 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// skip all space , usefull to get the texture even
// if there is a lot of space between the name and the
// path to the xpm
int	skip_space(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

// count the number of line inside a file and return it
int	count_line(char *argv)
{
	char	*str;
	int		nbline;
	int		fd;

	nbline = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (-1);
	str = get_next_line(fd);
	while (str != NULL)
	{
		nbline++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (nbline);
}

// copy the file argv[1] line by line and put it inside **map
// if the line is empty "\n\0" it is not copied
char	**loop_copy(int fd, int nb_line)
{
	char	*line;
	int		i;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (nb_line + 1));
	if (!map)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strcmp(line, "\n\0"))
		{
			map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	map[i] = NULL;
	return (map);
}

// make a copy of the map passed as argv[1]
char	**copy_map(char *argv)
{
	int		nb_line;
	int		fd;
	char	**map;

	nb_line = count_line(argv);
	if (nb_line == -1)
		return (NULL);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = loop_copy(fd, nb_line);
	close(fd);
	return (map);
}
