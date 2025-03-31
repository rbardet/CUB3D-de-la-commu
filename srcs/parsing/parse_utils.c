/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:25:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 22:52:11 by rbardet-         ###   ########.fr       */
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

// copy the playable part of the map and verify if its conform
// to the subject
char	**copy_and_check_map(t_cub *cub)
{
	char	**map;
	int		len;

	if (!check_base(cub->map + 7))
	{
		ft_putstr_fd("Error\nMap is not valid\n", 2);
		return (NULL);
	}
	len = find_max_len(cub->map + 7);
	if (len == 0)
		return (NULL);
	len = find_max_len(cub->map + 7);
	map = copy_tab(cub->map + 7);
	if (!map)
		return (NULL);
	free_tab(cub->map);
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
	cub->has_door = FALSE;
	cub->g_height = GRAPH_HEIGHT;
	cub->g_width = GRAPH_WIDTH;
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	cub->minimap = NULL;
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
