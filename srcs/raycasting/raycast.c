/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:48:55 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 13:34:45 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// get the starting point of the drawing and the end point
static t_ray	get_draw_size(t_ray ray)
{
	ray.draw_start = -ray.line_height / 2 + WIN_HEIGHT / 2;
	if (ray.draw_start < 0)
		ray.draw_start = 0;
	ray.draw_end = ray.line_height / 2 + WIN_HEIGHT / 2;
	if (ray.draw_end >= WIN_HEIGHT)
		ray.draw_end = WIN_HEIGHT - 1;
	return(ray);
}

// performm dda by advdancing  in both direction of the map
// if a wall is hit , the dda stop and we have the distance of the ray
static t_ray	perform_dda(t_cub *cub, t_ray ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray.map_x < 0
			|| ray.map_x >= cub->player.map_width || ray.map_y < 0
			|| ray.map_y >= cub->player.map_height)
			break ;
		if (ray.side_dist_x < ray.side_dist_y)
		{
			ray.side_dist_x += ray.delta_dist_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist_y += ray.delta_dist_y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		if (cub->map[ray.map_y][ray.map_x] == '1')
			hit = 1;
	}
	return(ray);
}

// calculate the height of the wall that will be drawn
static t_ray	calculate_wall_heigh(t_ray ray)
{
	if (ray.side == 0 && ray.ray_dir_x != 0)
		ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
	else if (ray.ray_dir_y != 0)
		ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
	ray.line_height = (int)(WIN_HEIGHT / ray.perp_wall_dist);
	return(ray);
}

// raycasting algorithm go from 0 to WIN_WIDTH
void	raycast(t_cub *cub)
{
	int		x;
	t_ray	ray;

	draw_ceilling(cub);
	draw_floor(cub);
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray = init_ray(cub, x);
		ray = ray_dist_x(cub, ray);
		ray = ray_dist_y(cub, ray);
		ray = perform_dda(cub, ray);
		ray = calculate_wall_heigh(ray);
		ray = get_draw_size(ray);
		draw_wall(cub, x, ray);
		x++;
	}
}
