/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:19:38 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/25 17:31:54 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	raycast(t_cub *cub)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
		double perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	for (x = 0; x < WIN_WIDTH; x++)
	{
		camera_x = 2 * x / (double)WIN_WIDTH - 1;
		ray_dir_x = cub->player.dir_x + cub->player.plane_x * camera_x;
		ray_dir_y = cub->player.dir_y + cub->player.plane_y * camera_x;
		map_x = (int)cub->player.x;
		map_y = (int)cub->player.y;
		double side_dist_x, side_dist_y;
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		int step_x, step_y, hit = 0, side;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (cub->player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - cub->player.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (cub->player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - cub->player.y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (cub->map[map_y][map_x] == '1')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - cub->player.x + (1 - step_x) / 2)
				/ ray_dir_x;
		else
			perp_wall_dist = (map_y - cub->player.y + (1 - step_y) / 2)
				/ ray_dir_y;
		line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;
		draw_vertical_line(cub, x, draw_start, draw_end, color);
	}
}
