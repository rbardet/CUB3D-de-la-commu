/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:01:57 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 16:19:19 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// find the distance that the ray will travell in Y
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

// find the distance that the ray will travell in X
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

// init the value for the calculation of the ray X
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
