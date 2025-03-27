/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:48:55 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 14:41:26 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_vertical_line(t_cub *cub, int x)
{
	int y;

	y = cub->raycast.draw_start;
	while (y <= cub->raycast.draw_end)
	{
		mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y, cub->raycast.color);
		y++;
	}
}

void	draw_floor_and_ceiling(t_cub *cub)
{
	int y;
	int x;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y,
				(cub->ceil.red << 16) | (cub->ceil.green << 8) | cub->ceil.blue);
			x++;
		}
		y++;
	}
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y,
				(cub->floor.red << 16) | (cub->floor.green << 8) | cub->floor.blue);
			x++;
		}
		y++;
	}
}

void	perform_dda(t_cub *cub)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub->raycast.map_x < 0 || cub->raycast.map_x >= cub->player.map_width || cub->raycast.map_y < 0 || cub->raycast.map_y >= cub->player.map_height)
			break;
		if (cub->raycast.side_dist_x < cub->raycast.side_dist_y)
		{
			cub->raycast.side_dist_x += cub->raycast.delta_dist_x;
			cub->raycast.map_x += cub->raycast.step_x;
			cub->raycast.side = 0;
		}
		else
		{
			cub->raycast.side_dist_y += cub->raycast.delta_dist_y;
			cub->raycast.map_y += cub->raycast.step_y;
			cub->raycast.side = 1;
		}
		if (cub->map[cub->raycast.map_y][cub->raycast.map_x] == '1')
			hit = 1;
	}
}

void	raycast(t_cub *cub)
{
	int x;

	draw_floor_and_ceiling(cub);
	x = 0;
	while (x < WIN_WIDTH)
	{
		cub->raycast.camera_x = 2 * x / (double)WIN_WIDTH - 1;
		cub->raycast.ray_dir_x = cub->player.dir_x + cub->player.plane_x * cub->raycast.camera_x;
		cub->raycast.ray_dir_y = cub->player.dir_y + cub->player.plane_y * cub->raycast.camera_x;
		cub->raycast.map_x = (int)cub->player.pos_x;
		cub->raycast.map_y = (int)cub->player.pos_y;

		if (cub->raycast.ray_dir_x == 0)
			cub->raycast.delta_dist_x = 1e30;
		else
			cub->raycast.delta_dist_x = fabs(1 / cub->raycast.ray_dir_x);

		if (cub->raycast.ray_dir_y == 0)
			cub->raycast.delta_dist_y = 1e30;
		else
			cub->raycast.delta_dist_y = fabs(1 / cub->raycast.ray_dir_y);

		if (cub->raycast.ray_dir_x < 0)
		{
			cub->raycast.step_x = -1;
			cub->raycast.side_dist_x = (cub->player.pos_x - cub->raycast.map_x) * cub->raycast.delta_dist_x;
		}
		else
		{
			cub->raycast.step_x = 1;
			cub->raycast.side_dist_x = (cub->raycast.map_x + 1.0 - cub->player.pos_x) * cub->raycast.delta_dist_x;
		}

		if (cub->raycast.ray_dir_y < 0)
		{
			cub->raycast.step_y = -1;
			cub->raycast.side_dist_y = (cub->player.pos_y - cub->raycast.map_y) * cub->raycast.delta_dist_y;
		}
		else
		{
			cub->raycast.step_y = 1;
			cub->raycast.side_dist_y = (cub->raycast.map_y + 1.0 - cub->player.pos_y) * cub->raycast.delta_dist_y;
		}

		perform_dda(cub);

		if (cub->raycast.side == 0 && cub->raycast.ray_dir_x != 0)
			cub->raycast.perp_wall_dist = (cub->raycast.side_dist_x - cub->raycast.delta_dist_x);
		else if (cub->raycast.ray_dir_y != 0)
			cub->raycast.perp_wall_dist = (cub->raycast.side_dist_y - cub->raycast.delta_dist_y);

		cub->raycast.line_height = (int)(WIN_HEIGHT / cub->raycast.perp_wall_dist);
		cub->raycast.draw_start = -cub->raycast.line_height / 2 + WIN_HEIGHT / 2;
		if (cub->raycast.draw_start < 0)
			cub->raycast.draw_start = 0;

		cub->raycast.draw_end = cub->raycast.line_height / 2 + WIN_HEIGHT / 2;
		if (cub->raycast.draw_end >= WIN_HEIGHT)
			cub->raycast.draw_end = WIN_HEIGHT - 1;

		if (cub->raycast.side == 1)
			cub->raycast.color = 0xAAAAAA;
		else
			cub->raycast.color = 0xFFFFFF;

		draw_vertical_line(cub, x);

		x++;
	}
}
