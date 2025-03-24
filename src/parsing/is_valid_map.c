/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:30:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/24 20:25:12 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// check if the map is conform , return FLALSE if itsn't else return TRUE
t_bool	is_valid_map(t_cub *cub)
{
	int	i;

	i = 0;
	if (ft_strncmp(cub->map[i], "NO ", 3)
		|| ft_strncmp(cub->map[i + 1], "SO ", 3)
		|| ft_strncmp(cub->map[i + 2], "WE ", 3)
		|| ft_strncmp(cub->map[i + 3], "EA ", 3)
		|| ft_strncmp(cub->map[i + 4], "DO ", 3))
		return (FALSE);
	i += 5;
	if (ft_strncmp(cub->map[i], "F ", 2)
		|| ft_strncmp(cub->map[i + 1], "C ", 2))
		return (FALSE);
	if (!is_one_player(cub->map, i + 2) || !is_close_map(cub->map, i + 2, cub))
		return (FALSE);
	return (TRUE);
}

// color the map with F starting from the map[y][x] position
// if the flood fill find an exit out of the map
// add 1 to the error count
void	flood_fill(int x, int y, char **map, int *ret)
{
	if (x < 0 || y < 0 || map[y][x] == '\n' || map[y][x] == '\0')
	{
		(*ret)++;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(x, y - 1, map, ret);
	flood_fill(x, y + 1, map, ret);
	flood_fill(x - 1, y, map, ret);
	flood_fill(x + 1, y, map, ret);
}

// if the map is close return FALSE else return TRUE
t_bool	close_or_not(char **map, int x, int y)
{
	int	ret;

	ret = 0;
	flood_fill(x, y, map, &ret);
	free_tab(map);
	if (ret)
		return (FALSE);
	return (TRUE);
}

// find the player pos and send the map inside a flood_fill
t_bool	is_close_map(char **map, int i, t_cub *cub)
{
	char	**copy;
	int		x;
	int		y;

	y = 0;
	copy = copy_tab(map + i);
	if (!copy)
		return (FALSE);
	while (copy[y])
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'N' || copy[y][x] == 'S'
				|| copy[y][x] == 'E' || copy[y][x] == 'W')
				break ;
			x++;
		}
		if (copy[y][x] != '\0')
			break ;
		y++;
	}
	cub->x = x;
	cub->y = y;
	return (close_or_not(copy, x, y));
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
