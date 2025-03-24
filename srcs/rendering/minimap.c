/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:10:20 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/24 23:22:22 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			mlx_pixel_put(cub->init_ptr, cub->win_ptr, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				draw_square(cub, j * 9, i * 9, 0xFF0000);
			else if (cub->map[i][j] == 'D')
				draw_square(cub, j * 9, i * 9, 0x2BFAFA);
			else if (cub->map[i][j] == cub->spawn_view)
				draw_square(cub, j * 9, i * 9, 0x00FF00);
			j++;
		}
		i++;
	}
}

int	minimap(t_cub *cub)
{
	if (!cub || !cub->init_ptr || !cub->win_ptr)
	{
		ft_putstr_fd("Error in minimap\n", 2);
		return (1);
	}
	render_minimap(cub);
	return (0);
}
