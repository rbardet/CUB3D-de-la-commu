/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:48:55 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 22:29:23 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// performm dda by advdancing  in both direction of the map
// if a wall is hit , the dda stop and we have the distance of the ray
void	perform_dda(t_cub *cub)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub->raycast.map_x < 0
			|| cub->raycast.map_x >= cub->player.map_width
			|| cub->raycast.map_y < 0
			|| cub->raycast.map_y >= cub->player.map_height)
			break ;
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

// calculate the height of the wall that will be drawn
void	calculate_wall_heigh(t_cub *cub)
{
	if (cub->raycast.side == 0 && cub->raycast.ray_dir_x != 0)
		cub->raycast.perp_wall_dist = (cub->raycast.side_dist_x
				- cub->raycast.delta_dist_x);
	else if (cub->raycast.ray_dir_y != 0)
		cub->raycast.perp_wall_dist = (cub->raycast.side_dist_y
				- cub->raycast.delta_dist_y);
	cub->raycast.line_height = (int)(WIN_HEIGHT / cub->raycast.perp_wall_dist);
}

// raycasting algorithm go from 0 to WIN_WIDTH
void	raycast(t_cub *cub)
{
	int	x;

	draw_ceilling(cub);
	draw_floor(cub);
	x = 0;
;	while (x < WIN_WIDTH)
	{
		init_ray(cub, x);
		ray_dist_x(cub);
		ray_dist_y(cub);
		perform_dda(cub);
		calculate_wall_heigh(cub);
		get_draw_size(cub);
		draw_wall(cub, x);
		x++;
	}
}
