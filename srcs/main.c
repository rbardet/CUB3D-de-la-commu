/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:50:07 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 18:58:40 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the given string is a .cub file.
 * @return TRUE if .cub, FALSE if not with an error message.
 */
t_bool	is_cub(char *argv)
{
	argv += ft_strlen(argv) - 4;
	if (!ft_strcmp(argv, ".cub"))
		return (TRUE);
	else
	{
		ft_putstr_fd("Error\nThe map is not a .cub\n", 2);
		return (FALSE);
	}
}

/**
 * @brief Get the max string length in a 2D array.
 * @param map 2D string array
 * @return Max string length or -1 if NULL.
 */
int	find_max_len(char **map)
{
	int	i;
	int	len;
	int	tmp_len;

	len = 0;
	i = 0;
	if (!map)
		return (-1);
	while (map[i])
	{
		tmp_len = ft_strlen(map[i]);
		if (tmp_len > len)
			len = tmp_len;
		i++;
	}
	return (len);
}

/**
 * @brief Entry point of the program.
 * The program takes one argument, a path to a .cub file.
 * The program parse the .cub file and make a raycasting of the map.
 * The program then launch a window with the raycasting of the map.
 * @param argc The number of argument passed to the program.
 * @param argv The argument passed to the program.
 * @return 0 if the program succeed, 127 if there is an error.
 */
int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nYou need to pass one map.\n", 2);
		return (127);
	}
	if (!is_cub(argv[1]))
		return (127);
	cub = parse_struct(argv[1]);
	if (!cub)
		return (127);
	cub->player.map_height = tab_size(cub->map);
	cub->player.map_width = find_max_len(cub->map);
	if (cub->player.map_width == -1 || cub->player.map_height == -1)
	{
		free_struct(cub);
		ft_putstr_fd("Error while calculating map size\n", 2);
		return (127);
	}
	print_struct(cub);
	open_window(cub);
	return (0);
}
