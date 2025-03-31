/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:30:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 22:43:39 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	t_bool	is_valid_param(char *line)
{
	if (ft_strncmp(line, "NO ", 3)
		&& ft_strncmp(line, "SO ", 3)
		&& ft_strncmp(line, "WE ", 3)
		&& ft_strncmp(line, "EA ", 3)
		&& ft_strncmp(line, "F ", 2)
		&& ft_strncmp(line, "C ", 2)
		&& ft_strncmp(line, "DO ", 3))
		return (FALSE);
	else
		return (TRUE);
}

// check if the map is conform , return FALSE if itsn't else return TRUE
t_bool	is_valid_map(t_cub *cub)
{
	int	i;
	int	has_door;

	i = 0;
	has_door = 0;
	if (cub->has_door == FALSE)
		has_door = 1;
	while (cub->map[i] && i < 7 - has_door)
	{
		if (!is_valid_param(cub->map[i]))
			return (FALSE);
		if (!ft_strncmp(cub->map[i], "DO ", 3)
			&& cub->has_door == FALSE)
			return (FALSE);
		i++;
	}
	while (cub->map[i] && ft_strcmp(cub->map[i], "\n\0"))
		i++;
	if (!is_one_player(cub->map, i) || !is_close_map(cub->map, i, cub))
		return (FALSE);
	return (TRUE);
}

// check if there is only one player if no return FALSE else return TRUE
t_bool	is_one_player(char **map, int i)
{
	char	**copy;
	int		j;
	int		k;
	int		nb_player;

	j = 0;
	nb_player = 0;
	copy = copy_tab(map + i);
	if (!copy)
		return (FALSE);
	while (copy[j])
	{
		k = 0;
		while (copy[j][k])
		{
			if (copy[j][k] == 'N' || copy[j][k] == 'S'
				|| copy[j][k] == 'E' || copy[j][k] == 'W')
				nb_player++;
			k++;
		}
		j++;
	}
	if (nb_player != 1)
		return (free_tab(copy), FALSE);
	return (free_tab(copy), TRUE);
}
