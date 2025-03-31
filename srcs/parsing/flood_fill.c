/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:43:09 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 22:45:08 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// color the map with F starting from the map[y][x] position
// if the flood fill find an exit out of the map
// add 1 to the error count
void	flood_fill(int x, int y, char **map, int *ret)
{
	if (y < 0 || (size_t)x > ft_strlen(map[y]) || x < 0
		|| map[y][x] == '\n' || map[y][x] == '\0' || map[y][x] == ' ')
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
t_bool	close_or_not(char **map, int x, int y, t_cub *cub)
{
	int	ret;

	cub->spawn_view = map[y][x];
	cub->player.pos_x = (double)x;
	cub->player.pos_y = (double)y;
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
	x = 0;
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
	return (close_or_not(copy, x, y, cub));
}
