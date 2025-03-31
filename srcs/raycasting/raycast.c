/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:48:55 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 22:06:48 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// get the color of the pixel inside the texture
int32_t	get_texture_color(mlx_texture_t *texture, int texX, int texY)
{
	uint8_t	*pixels;
	int		pixel_index;

	if (!texture || !texture->pixels)
		return (0);
	// Vérification des limites de la texture
	if ((uint32_t)texX >= texture->width || (uint32_t)texY >= texture->height)
		return (0);
	// Calcul de l'index correct (4 canaux par pixel : RGBA)
	pixel_index = (texY * texture->width + texX) * 4;
	pixels = texture->pixels;
	return ((pixels[pixel_index] << 24)
		| (pixels[pixel_index + 1] << 16)
		| (pixels[pixel_index + 2] << 8)
		| pixels[pixel_index + 3]);
}

// get the starting point of the drawing and the end point
static t_ray	get_draw_size(t_ray ray)
{
	ray.draw_start = -ray.line_height / 2 + WIN_HEIGHT / 2;
	if (ray.draw_start < 0)
		ray.draw_start = 0;
	ray.draw_end = ray.line_height / 2 + WIN_HEIGHT / 2;
	if (ray.draw_end >= WIN_HEIGHT)
		ray.draw_end = WIN_HEIGHT - 1;
	return (ray);
}

// performm dda by advdancing  in both direction of the map
// if a wall is hit , the dda stop and we have the distance of the ray
t_ray	perform_dda(t_cub *cub, t_ray ray, t_bool is_open)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray.map_x < 0 || ray.map_x >= cub->player.map_width || ray.map_y < 0
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
		if (cub->map[ray.map_y][ray.map_x] == '1'
			|| cub->map[ray.map_y][ray.map_x] == 'D')
			hit = 1;
		if (cub->map[ray.map_y][ray.map_x] == '2' && is_open == FALSE)
			hit = 1;
	}
	return (ray);
}

// calculate the height of the wall that will be drawn
static t_ray	calculate_wall_heigh(t_ray ray)
{
	if (ray.side == 0)
		ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
	else
		ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
	if (ray.perp_wall_dist < 0.01)
		ray.perp_wall_dist = 0.01;
	if (ray.perp_wall_dist == 0)
		ray.perp_wall_dist = 0.000001;
	ray.line_height = (int)(WIN_HEIGHT / fabs(ray.perp_wall_dist));
	return (ray);
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
		ray = perform_dda(cub, ray, TRUE);
		ray = calculate_wall_heigh(ray);
		ray = get_draw_size(ray);
		draw_wall(cub, x, ray);
		x++;
	}
	minimap(cub);
}
