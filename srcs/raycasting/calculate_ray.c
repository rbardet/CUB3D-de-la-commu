/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:01:57 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 21:02:05 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// find the distance that the ray will travell in Y
void	ray_dist_y(t_cub *cub)
{
	if (cub->raycast.ray_dir_y < 0)
	{
		cub->raycast.step_y = -1;
		cub->raycast.side_dist_y = (cub->player.pos_y - cub->raycast.map_y)
			* cub->raycast.delta_dist_y;
	}
	else
	{
		cub->raycast.step_y = 1;
		cub->raycast.side_dist_y = (cub->raycast.map_y + 1.0
				- cub->player.pos_y) * cub->raycast.delta_dist_y;
	}
}

// find the distance that the ray will travell in X
void	ray_dist_x(t_cub *cub)
{
	if (cub->raycast.ray_dir_x < 0)
	{
		cub->raycast.step_x = -1;
		cub->raycast.side_dist_x = (cub->player.pos_x - cub->raycast.map_x)
			* cub->raycast.delta_dist_x;
	}
	else
	{
		cub->raycast.step_x = 1;
		cub->raycast.side_dist_x = (cub->raycast.map_x + 1.0
				- cub->player.pos_x) * cub->raycast.delta_dist_x;
	}
}

// init the value for the calculation of the ray X
void	init_ray(t_cub *cub, int x)
{
	cub->raycast.camera_x = 2 * x / (double)WIN_WIDTH - 1;
	cub->raycast.ray_dir_x = cub->player.dir_x + cub->player.plane_x
		* cub->raycast.camera_x;
	cub->raycast.ray_dir_y = cub->player.dir_y + cub->player.plane_y
		* cub->raycast.camera_x;
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
}
