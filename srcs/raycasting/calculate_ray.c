/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:01:57 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/30 19:19:03 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Calculates ray's Y distance and step direction in the map grid.
 * @param cub The game structure containing player information.
 * @param ray The raycasting structure.
 * @return The updated ray structure with calculated side_dist_y and step_y.
 */
t_ray	ray_dist_y(t_cub *cub, t_ray ray)
{
	if (ray.ray_dir_y < 0)
	{
		ray.step_y = -1;
		ray.side_dist_y = (cub->player.pos_y - ray.map_y) * ray.delta_dist_y;
	}
	else
	{
		ray.step_y = 1;
		ray.side_dist_y = (ray.map_y + 1.0 - cub->player.pos_y)
			* ray.delta_dist_y;
	}
	return (ray);
}

/**
 * @brief Calculates ray's X distance and step direction in the map grid.
 * @param cub The game structure.
 * @param ray The raycasting structure.
 * @return Updated ray structure with calculated side_dist_x and step_x.
 */
t_ray	ray_dist_x(t_cub *cub, t_ray ray)
{
	if (ray.ray_dir_x < 0)
	{
		ray.step_x = -1;
		ray.side_dist_x = (cub->player.pos_x - ray.map_x) * ray.delta_dist_x;
	}
	else
	{
		ray.step_x = 1;
		ray.side_dist_x = (ray.map_x + 1.0 - cub->player.pos_x)
			* ray.delta_dist_x;
	}
	return (ray);
}

/**
 * @brief Initializes a ray structure for the given screen pixel.
 * @param cub The game structure containing player information.
 * @param x The screen pixel coordinate (0-799).
 * @return The initialized ray structure.
 */
t_ray	init_ray(t_cub *cub, int x)
{
	t_ray	ray;

	ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray.ray_dir_x = cub->player.dir_x + cub->player.plane_x * ray.camera_x;
	ray.ray_dir_y = cub->player.dir_y + cub->player.plane_y * ray.camera_x;
	ray.map_x = (int)cub->player.pos_x;
	ray.map_y = (int)cub->player.pos_y;
	if (ray.ray_dir_x == 0)
		ray.delta_dist_x = 1e30;
	else
		ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
	if (ray.ray_dir_y == 0)
		ray.delta_dist_y = 1e30;
	else
		ray.delta_dist_y = fabs(1 / ray.ray_dir_y);
	return (ray);
}
