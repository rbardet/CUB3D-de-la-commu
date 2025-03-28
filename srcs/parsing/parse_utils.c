/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:25:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 20:24:12 by rbardet-         ###   ########.fr       */
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
		i++;
	}
	return (TRUE);
}

// copy the playable part of the map and verify if its conform
// to the subject
char	**copy_and_check_map(t_cub *cub)
{
	char	**map;

	map = copy_tab(cub->map + 7);
	if (!map)
		return (NULL);
	free_tab(cub->map);
	if (!check_base(map))
	{
		ft_putstr_fd("Error\nMap is not valid\n", 2);
		return (free_tab(map), NULL);
	}
	return (map);
}

// put all the pointer inside the struct at NULL
t_cub	*init_struct(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		ft_putstr_fd("Error\nFailed to init struct\n", 2);
		return (NULL);
	}
	cub->g_height = GRAPH_HEIGHT;
	cub->g_width = GRAPH_WIDTH;
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	cub->no_xpm = NULL;
	cub->so_xpm = NULL;
	cub->we_xpm = NULL;
	cub->ea_xpm = NULL;
	cub->do_xpm = NULL;
	cub->init_ptr = NULL;
	cub->img_ptr = NULL;
	cub->map = NULL;
	return (cub);
}
