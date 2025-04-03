/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:25:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/03 12:16:37 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**sort_arg(char **tab, t_cub *cub)
{
	int		i;
	char	**tmp;
	char	**sorted;
	int		has_door;

	i = 0;
	has_door = 0;
	if (cub->has_door == TRUE)
		has_door = 1;
	tmp = malloc(sizeof(char *) * (8));
	if (!tmp)
		return (NULL);
	while (tab[i] && i != 6 + has_door)
	{
		tmp[i] = ft_strdup(tab[i]);
		if (!tmp[i])
			return (free_tab(tmp), NULL);
		i++;
	}
	tmp[i] = NULL;
	sorted = sort_str_tab(tmp);
	free_tab(tmp);
	return (sorted);
}

// go threw the map and check if the character is allowed
// if not return FALSE else return TRUE
t_bool	check_base(char **tab)
{
	char	*base;
	int		i;
	int		j;
	int		b;

	base = "01NSWED \n";
	i = -1;
	while (tab[++i])
	{
		j = 0;
		while (tab[i][++j])
		{
			b = 0;
			while (base[b] != '\0')
			{
				if (tab[i][j] == base[b])
					break ;
				b++;
			}
			if (base[b] == '\0')
				return (FALSE);
		}
	}
	return (TRUE);
}

static void	copy_line(int max_len, int i, char **map, char **new_map)
{
	int	j;

	j = 0;
	while (map[i][j] != '\n' && j < max_len)
	{
		new_map[i][j] = map[i][j];
		j++;
	}
	while (j < max_len)
	{
		new_map[i][j] = '\0';
		j++;
	}
	new_map[i][j] = '\0';
}

static char	**copy_map_max_size(char **map, int max_len)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = malloc(sizeof(char *) * (tab_size(map) + 1));
	if (!new_map)
		return (NULL);
	while (map[i])
	{
		new_map[i] = malloc(sizeof(char) * (max_len + 1));
		if (!new_map[i])
			return (NULL);
		copy_line(max_len, i, map, new_map);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

// copy the playable part of the map and verify if its conform
// to the subject
char	**copy_and_check_map(t_cub *cub)
{
	char	**map;
	int		len;
	int		has_door;

	has_door = 0;
	if (cub->has_door == false)
		has_door = 1;
	if (!check_base(cub->map + 7))
	{
		free_tab(cub->map);
		ft_putstr_fd("Error\nMap is not valid\n", 2);
		return (NULL);
	}
	len = find_max_len(cub->map + 7);
	if (len == 0)
		return (NULL);
	len = find_max_len(cub->map + 7);
	map = copy_map_max_size(cub->map + 7 - has_door, len);
	if (!map)
		return (NULL);
	free_tab(cub->map);
	return (map);
}
