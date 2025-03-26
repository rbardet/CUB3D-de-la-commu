/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:30:31 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/26 17:53:25 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// convert the rgb code in the char ** in a new t_rgb
// if the rgb is not in range of 0 to 255 or contain a letter
// set the value to -1 otherwise give it the code
t_rgb	get_rgb(char **rgb_tmp)
{
	t_rgb	rgb;
	int		i;
	int		tmp;
	char	*trim;

	i = skip_space(rgb_tmp[0], 2);
	tmp = ft_atoi(rgb_tmp[0] + i);
	trim = ft_strtrim(rgb_tmp[2], "\n");
	if (tmp < 0 || tmp > 255 || !ft_isdigital(rgb_tmp[0] + i))
		rgb.red = -1;
	else
		rgb.red = tmp;
	tmp = ft_atoi(rgb_tmp[1]);
	if (tmp < 0 || tmp > 255 || !ft_isdigital(rgb_tmp[1]))
		rgb.green = -1;
	else
		rgb.green = tmp;
	tmp = ft_atoi(rgb_tmp[2]);
	if (tmp < 0 || tmp > 255 || !ft_isdigital(trim))
		rgb.blue = -1;
	else
		rgb.blue = tmp;
	free(trim);
	return (rgb);
}

// extract all the xpm of the map inside the struct
void	get_xpm(t_cub *cub)
{
	int		i;
	int		g_height;
	int		g_width;

	g_height = GRAPH_HEIGHT;
	g_width = GRAPH_WIDTH;
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	cub->win_ptr = NULL;
	i = skip_space(cub->map[0], 3);
	cub->no_xpm = mlx_xpm_file_to_image(cub->init_ptr, "./graphic/NO.xpm",
			&g_width, &g_height);
	i = skip_space(cub->map[1], 3);
	cub->so_xpm = mlx_xpm_file_to_image(cub->init_ptr, "./graphic/SO.xpm",
			&g_width, &g_height);
	i = skip_space(cub->map[2], 3);
	cub->we_xpm = mlx_xpm_file_to_image(cub->init_ptr, "./graphic/WE.xpm",
			&g_width, &g_height);
	i = skip_space(cub->map[3], 3);
	cub->ea_xpm = mlx_xpm_file_to_image(cub->init_ptr, "./graphic/EA.xpm",
			&g_width, &g_height);
	i = skip_space(cub->map[4], 3);
	cub->do_xpm = mlx_xpm_file_to_image(cub->init_ptr, "./graphic/DO.xpm",
			&g_width, &g_height);
}

// fill the struct with all the data for the rendering
// add in the xpm , rgb code for floor and ceilling
// and a copy of the map
t_cub	*fill_struct(t_cub *cub)
{
	char	**map;
	char	**rgb_tmp;

	get_xpm(cub);
	rgb_tmp = ft_split(cub->map[5], ',');
	if (!rgb_tmp || tab_size(rgb_tmp) != 3)
		return (free_tab(rgb_tmp), free_struct(cub), NULL);
	cub->floor = get_rgb(rgb_tmp);
	free_tab(rgb_tmp);
	rgb_tmp = ft_split(cub->map[6], ',');
	if (!rgb_tmp || tab_size(rgb_tmp) != 3)
		return (free_tab(rgb_tmp), free_struct(cub), NULL);
	cub->ceil = get_rgb(rgb_tmp);
	free_tab(rgb_tmp);
	map = copy_tab(cub->map + 7);
	free_tab(cub->map);
	cub->map = copy_tab(map);
	if (cub->floor.red == -1 || cub->floor.green == -1
		|| cub->floor.blue == -1 || cub->ceil.red == -1
		|| cub->ceil.green == -1 || cub->ceil.blue == -1)
	{
		ft_putstr_fd("Error\nOne rgb code is not valid\n", 2);
		return (free_tab(map), free_struct(cub), NULL);
	}
	return (free_tab(map), cub);
}

// init the player viewpoint at the start of the rendering
t_player	init_player_struct(t_cub *cub)
{
	t_player	player;

	if (cub->spawn_view == 'N')
	{
		player.dir_x = 0;
		player.dir_y = 1;
	}
	else if (cub->spawn_view == 'S')
	{
		player.dir_x = 0;
		player.dir_y = -1;
	}
	else if (cub->spawn_view == 'W')
	{
		player.dir_x = -1;
		player.dir_y = 0;
	}
	else if (cub->spawn_view == 'E')
	{
		player.dir_x = 1;
		player.dir_y = 0;
	}
	player.plane_x = PLANE_FACTOR * (-player.dir_x);
	player.plane_y = PLANE_FACTOR * (player.dir_y);
	return (player);
}

// parse_struct will put in the main struct t_cub *cub all the data needed
// for the render (path to the xpm, rgb for the floor and ceilling and a
// char ** for the map)
t_cub	*parse_struct(char *argv)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->map = copy_map(argv);
	if (!cub->map)
		return (free(cub), NULL);
	if (!is_valid_map(cub))
	{
		ft_putstr_fd("Error\nThe map is not valid\n", 2);
		return (free_tab(cub->map), free(cub), NULL);
	}
	cub->init_ptr = mlx_init();
	if (!cub->init_ptr)
	{
		ft_putstr_fd("Error\nCouldn't init the window pointer\n", 2);
		return (NULL);
	}
	cub = fill_struct(cub);
	if (!cub)
		return (NULL);
	cub->player = init_player_struct(cub);
	return (cub);
}
