/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:25:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 22:23:22 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		while (tab[i][j])
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
			j++;
		}
		i++;
	}
	return (TRUE);
}

char	**copy_and_check_map(t_cub *cub)
{
	char	**map;

	cub->img = NULL;
	map = copy_tab(cub->map + 7);
	if (!map)
		return (NULL);
	free_tab(cub->map);
	if (!check_base(map))
		return (free_tab(map), NULL);
	return (map);
}
