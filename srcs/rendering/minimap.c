/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:10:20 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 11:57:01 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE)
	{
		j = 0;
		while (j < TILE)
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
				draw_square(cub, j * TILE, i * TILE, 0xF08080);
			if (cub->map[i][j] == '0')
				draw_square(cub, j * TILE, i * TILE, 0xFFDAB9);
			else if (cub->map[i][j] == 'D')
				draw_square(cub, j * TILE, i * TILE, 0x2BFAFA);
			else if (i == cub->player.pos_x && j == cub->player.pos_y)
			{
				draw_square(cub, j * TILE, i * TILE, 0x00FF00);
				draw_square(cub, j * TILE, i * TILE - 15, 0xF0FFF0);
			}
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
