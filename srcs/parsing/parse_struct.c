/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:30:31 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 17:43:06 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// convert the rgb code in the char ** in a new t_rgb
// if the rgb is not in range of 0 to 255 or contain a letter
// set the value to -1 otherwise give it the code
static t_rgb	get_rgb(char **rgb_tmp)
{
	t_rgb	rgb;
	int		i;
	int32_t	tmp;
	char	*trim;

	i = skip_space(rgb_tmp[0], 2);
	tmp = (int32_t)ft_atoi(rgb_tmp[0] + i);
	trim = ft_strtrim(rgb_tmp[2], "\n");
	if (tmp < 0 || tmp > 255 || !ft_isdigital(rgb_tmp[0] + i))
		rgb.red = -1;
	else
		rgb.red = tmp;
	tmp = (int32_t)ft_atoi(rgb_tmp[1]);
	if (tmp < 0 || tmp > 255 || !ft_isdigital(rgb_tmp[1]))
		rgb.green = -1;
	else
		rgb.green = tmp;
	tmp = (int32_t)ft_atoi(rgb_tmp[2]);
	if (tmp < 0 || tmp > 255 || !ft_isdigital(trim))
		rgb.blue = -1;
	else
		rgb.blue = tmp;
	free(trim);
	return (rgb);
}

// copy the line to the \n and return it , its a char * to the png
char	*copy_png(char *line)
{
	char	*text;
	int		i;

	text = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!text)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		text[i] = line[i];
		i++;
	}
	text[i] = '\0';
	return (text);
}

// extract the png from the map and return it
static mlx_texture_t *get_png(t_cub *cub, int idx)
{
	int				i;
	mlx_texture_t	*text;
	char			*tmp;

	i = skip_space(cub->map[idx], 3);
	tmp = copy_png(cub->map[idx] + i);
	if (!tmp)
		return (NULL);
	text = mlx_load_png(tmp);
	if (!text)
		return (NULL);
	free(tmp);
	return (text);
}

// load all the png inside the cub struct
static void	load_png(t_cub *cub)
{
	cub->no_xpm = get_png(cub, 0);
	if (!cub->no_xpm)
		ft_putstr_fd("Error\nFailed to load North texture\n", 2);
	cub->so_xpm = get_png(cub, 1);
	if (!cub->so_xpm)
		ft_putstr_fd("Error\nFailed to load South texture\n", 2);
	cub->we_xpm = get_png(cub, 2);
	if (!cub->we_xpm)
		ft_putstr_fd("Error\nFailed to load West texture\n", 2);
	cub->ea_xpm = get_png(cub, 3);
	if (!cub->ea_xpm)
		ft_putstr_fd("Error\nFailed to load East texture\n", 2);
	cub->do_xpm = get_png(cub, 4);
	if (!cub->do_xpm)
		ft_putstr_fd("Error\nFailed to load Door texture\n", 2);
}

// fill the struct with all the data for the rendering
// add in the xpm , rgb code for floor and ceilling
// and a copy of the map
static t_cub	*fill_struct(t_cub *cub)
{
	char	**rgb_tmp;

	load_png(cub);
	if (!cub->no_xpm || !cub->so_xpm || !cub->ea_xpm || !cub->we_xpm || !cub->do_xpm)
		return (free_struct(cub), NULL);
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
	cub->map = copy_and_check_map(cub);
	if (!cub->map)
		return (free_struct(cub), NULL);
	if (cub->floor.red == -1 || cub->floor.green == -1
		|| cub->floor.blue == -1 || cub->ceil.red == -1
		|| cub->ceil.green == -1 || cub->ceil.blue == -1)
	{
		ft_putstr_fd("Error\nOne rgb code is not valid\n", 2);
		return (free_struct(cub), NULL);
	}
	return (cub);
}

// init the player viewpoint at the start of the rendering
t_player	init_player_struct(t_cub *cub, t_player player)
{
	if (cub->spawn_view == 'N')
	{
		player.dir_x = 0;
		player.dir_y = -1;
	}
	else if (cub->spawn_view == 'S')
	{
		player.dir_x = 0;
		player.dir_y = 1;
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
	cub->map = copy_map(argv);
	if (!cub->map)
		return (free(cub), NULL);
	if (!is_valid_map(cub))
	{
		ft_putstr_fd("Error\nThe map is not valid\n", 2);
		return (free_tab(cub->map), free(cub), NULL);
	}
	cub->init_ptr = mlx_init(cub->win_width, cub->win_height, "CUB3D", FALSE);
	if (!cub->init_ptr)
	{
		ft_putstr_fd("Error\nmlx_init failed\n", 2);
		return (free_struct(cub), NULL);
	}
	cub = fill_struct(cub);
	if (!cub)
		return (NULL);
	cub->player.plane_factor = (tan((FOV_ANGLE * M_PI / 180) / 2));
	cub->player = init_player_struct(cub, cub->player);
	return (cub);
}
