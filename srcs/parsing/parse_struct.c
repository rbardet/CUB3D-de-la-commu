/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:30:31 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/03 12:54:27 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_cub	*handle_rgb_error(t_cub *cub)
{
	if (cub->floor.red == -1 || cub->floor.green == -1
		|| cub->floor.blue == -1 || cub->ceil.red == -1
		|| cub->ceil.green == -1 || cub->ceil.blue == -1)
	{
		ft_putstr_fd("Error\nOne rgb code is not valid\n", 2);
		return (free_struct(cub), NULL);
	}
	return (cub);
}

static t_cub	*fill_struct_utils(t_cub *cub, int has_door, char **tmp)
{
	char	**rgb_tmp;

	rgb_tmp = ft_split(tmp[0], ',');
	if (!rgb_tmp || tab_size(rgb_tmp) != 3)
		return (free_tab(rgb_tmp), free_tab(tmp), free_struct(cub), NULL);
	cub->ceil = get_rgb(rgb_tmp);
	free_tab(rgb_tmp);
	rgb_tmp = ft_split(tmp[2 + has_door], ',');
	if (!rgb_tmp || tab_size(rgb_tmp) != 3)
		return (free_tab(rgb_tmp), free_tab(tmp), free_struct(cub), NULL);
	cub->floor = get_rgb(rgb_tmp);
	free_tab(rgb_tmp);
	free_tab(tmp);
	cub->map = copy_and_check_map(cub);
	if (!cub->map)
		return (free_struct(cub), NULL);
	return (cub);
}

// fill the struct with all the data for the rendering
// add in the xpm , rgb code for floor and ceilling
// and a copy of the map
static t_cub	*fill_struct(t_cub *cub)
{
	char	**tmp;
	int		has_door;

	has_door = 0;
	if (cub->has_door == TRUE)
		has_door += 1;
	tmp = sort_arg(cub->map, cub);
	if ((tab_size(tmp) != 6 && cub->has_door == FALSE)
		|| (tab_size(tmp) != 7 && cub->has_door == TRUE))
		return (free_struct(cub), free_tab(tmp), NULL);
	load_png(cub, tmp);
	if (!cub->no_xpm || !cub->so_xpm || !cub->ea_xpm
		|| !cub->we_xpm || (!cub->do_xpm && cub->has_door == TRUE))
		return (free_tab(tmp), free_struct(cub), NULL);
	cub = fill_struct_utils(cub, has_door, tmp);
	if (!cub)
		return (NULL);
	if (cub->do_xpm && !ft_tabchr(cub->map, 'D'))
	{
		ft_putstr_fd("Error\nDoor texture detected but no door on map\n", 2);
		return (free_struct(cub), NULL);
	}
	return (handle_rgb_error(cub));
}

// init the player viewpoint at the start of the rendering
t_player	init_player_struct(t_cub *cub, t_player player)
{
	if (cub->spawn_view == 'N')
	{
		player.dir_x = 0.005;
		player.dir_y = -1.005;
	}
	else if (cub->spawn_view == 'S')
	{
		player.dir_x = 0.005;
		player.dir_y = 1.005;
	}
	else if (cub->spawn_view == 'W')
	{
		player.dir_x = -1.005;
		player.dir_y = 0.005;
	}
	else if (cub->spawn_view == 'E')
	{
		player.dir_x = 1.005;
		player.dir_y = 0.005;
	}
	player.plane_x = player.dir_y * cub->player.plane_factor;
	player.plane_y = -player.dir_x * cub->player.plane_factor;
	return (player);
}

// parse_struct will put in the main struct t_cub *cub all the data needed
// for the render (path to the xpm, rgb for the floor and ceilling and a
// char ** for the map)
t_cub	*parse_struct(char *argv)
{
	t_cub	*cub;

	cub = init_struct();
	if (!cub)
		return (NULL);
	cub->map = copy_map(argv, cub);
	if (!cub->map)
		return (free_struct(cub), NULL);
	if (!is_valid_map(cub))
	{
		ft_putstr_fd("Error\nThe map is not valid\n", 2);
		return (free_tab(cub->map), free(cub), NULL);
	}
	cub->init_ptr = mlx_init(cub->win_width, cub->win_height, "CUB3D", FALSE);
	if (!cub->init_ptr)
		return (free_struct(cub), NULL);
	cub = fill_struct(cub);
	if (!cub)
		return (NULL);
	init_sprite(cub);
	if (!cub)
		return (NULL);
	cub->player.plane_factor = ((FOV_ANGLE * M_PI / 180) / 2);
	cub->player = init_player_struct(cub, cub->player);
	return (cub);
}
