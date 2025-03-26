/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:55:36 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/27 00:03:36 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_xpm_status(void *xpm, char *name)
{
	if (xpm)
		printf("✅  %s XPM: Loaded\n", name);
	else
		printf("❌  %s XPM: Not loaded\n", name);
}

char	*get_direction_name(char c)
{
	if (c == 'N')
		return ("North");
	if (c == 'S')
		return ("South");
	if (c == 'W')
		return ("West");
	if (c == 'E')
		return ("East");
	return ("Unknown");
}

void	print_window_info(t_cub *cub)
{
	printf("\n\033[1;34m[Window Info]\033[0m\n");
	printf("Window Size: %dx%d\n", cub->win_width, cub->win_height);
	printf("MLX Init Ptr: %p\n", cub->init_ptr);
	printf("Window Ptr: %p\n", cub->win_ptr);
}

void	print_textures_info(t_cub *cub)
{
	printf("\n\033[1;34m[Textures]\033[0m\n");
	print_xpm_status(cub->no_xpm, "North");
	print_xpm_status(cub->so_xpm, "South");
	print_xpm_status(cub->we_xpm, "West");
	print_xpm_status(cub->ea_xpm, "East");
	print_xpm_status(cub->do_xpm, "Door");
}

void	print_colors_info(t_cub *cub)
{
	printf("\n\033[1;34m[Colors]\033[0m\n");
	printf("Floor: R:%d G:%d B:%d\n", cub->floor.red, cub->floor.green,
		cub->floor.blue);
	printf("Ceiling: R:%d G:%d B:%d\n", cub->ceil.red, cub->ceil.green,
		cub->ceil.blue);
}
