/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:10:20 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 20:22:39 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// draw a square of 9 pixel of a given color at x y pos
static void	draw_square(t_cub *cub, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			mlx_put_pixel(cub->minimap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// go threw the start x and y to the end x and y and draw
// the player surounding on a minimap
static void	draw_minimap(t_cub *cub, t_mini mini)
{
	int	i;
	int	j;

	i = mini.start_y;
	while (i <= mini.end_y)
	{
		j = mini.start_x;
		while (j <= mini.end_x)
		{
			if (cub->map[i][j] == '1')
				draw_square(cub, (j - mini.start_x) * 9, (i - mini.start_y) * 9, 0xFF808080);
			else if (cub->map[i][j] == '0' || cub->map[i][j] == cub->spawn_view)
				draw_square(cub, (j - mini.start_x) * 9, (i - mini.start_y) * 9, 0xFFFFFFFF);
			else if (cub->map[i][j] == 'D')
				draw_square(cub, (j - mini.start_x) * 9, (i - mini.start_y) * 9, 0x0000FFFF);
			else if (cub->map[i][j] == '2')
				draw_square(cub, (j - mini.start_x) * 9, (i - mini.start_y) * 9, 0x00FF00FF);
			else
				draw_square(cub, (j - mini.start_x) * 9, (i - mini.start_y) * 9, 0xFF808080);
			j++;
		}
		i++;
	}
}

// calculate the player surounding for the draw of the minimap
// we need to know where the map stop because the program
// cant check in the negative value of x and y
// so if we see an indice out of limit we resize it to acceptable value
static void	calculate_player_suround(t_cub *cub)
{
	t_mini	mini;

	mini.start_x = (int)cub->player.pos_x - 8;
	mini.start_y = (int)cub->player.pos_y - 8;
	mini.end_x = (int)cub->player.pos_x + 8;
	mini.end_y = (int)cub->player.pos_y + 8;
	if (mini.start_x < 0)
		mini.start_x = 0;
	if (mini.start_y < 0)
		mini.start_y = 0;
	if (mini.end_x >= cub->player.map_width)
		mini.end_x = cub->player.map_width - 1;
	if (mini.end_y >= cub->player.map_height)
		mini.end_y = cub->player.map_height - 1;
	draw_minimap(cub, mini);
	draw_square(cub, ((int)cub->player.pos_x - mini.start_x) * 9,
		((int)cub->player.pos_y - mini.start_y) * 9, 0xFF0000FF);
}

void	minimap(t_cub *cub)
{
	if (!cub || !cub->init_ptr)
	{
		ft_putstr_fd("Error in minimap\n", 2);
		return ;
	}
	calculate_player_suround(cub);
	return ;
}
