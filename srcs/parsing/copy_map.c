/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 02:20:17 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 21:32:54 by rbardet-         ###   ########.fr       */
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
static int	count_line(char *argv, t_cub *cub)
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
		if (ft_strchr(str, 'D'))
			cub->has_door = TRUE;
		nbline++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (nbline);
}

// copy the file argv[1] line by line and put it inside **map
// if the line is empty "\n\0" it is not copied
static char	**loop_copy(int fd, int nb_line, t_cub *cub)
{
	char	*line;
	int		i;
	char	**map;
	int		lim;

	i = 0;
	lim = 6;
	(void)cub;
	map = malloc(sizeof(char *) * (nb_line + 1));
	if (!map)
		return (NULL);
	if (cub->has_door == TRUE)
		lim++;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (lim != 0 && ft_strcmp(line, "\n\0"))
		{
			map[i] = ft_strdup(line);
			i++;
			lim--;
		}
		else if (lim == 0)
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
char	**copy_map(char *argv, t_cub *cub)
{
	int		nb_line;
	int		fd;
	char	**map;

	nb_line = count_line(argv, cub);
	if (nb_line == -1)
		return (NULL);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = loop_copy(fd, nb_line, cub);
	close(fd);
	if (!map)
	{
		ft_putstr_fd("Error\nMap is not valid\n", 2);
		return (NULL);
	}
	return (map);
}
