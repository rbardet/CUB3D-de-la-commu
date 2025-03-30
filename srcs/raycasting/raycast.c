/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:48:55 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/30 19:37:08 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Retrieves the color of a pixel from a texture.
 * Returns the pixel color at specified coordinates within a texture as an
 * int32_t in the format 0xAABBGGRR (alpha, blue, green, red).
 * @param texture The texture to get the color from.
 * @param texX The x coordinate of the pixel in the texture.
 * @param texY The y coordinate of the pixel in the texture.
 * @return The color of the pixel as an int32_t.
 */
int32_t	get_texture_color(mlx_texture_t *texture, int texX, int texY)
{
	uint8_t	*pixels;
	int		pixel_index;

	if (!texture || !texture->pixels)
		return (0);
	if ((uint32_t)texX >= texture->width || (uint32_t)texY >= texture->height)
		return (0);
	pixel_index = (texY * texture->width + texX) * 4;
	pixels = texture->pixels;
	return ((pixels[pixel_index] << 24)
		| (pixels[pixel_index + 1] << 16)
		| (pixels[pixel_index + 2] << 8)
		| pixels[pixel_index + 3]);
}

/**
 * @brief Calculates the boundaries of a ray to be drawn.
 * @param ray The ray structure.
 * @return The ray structure with the updated draw start and end.
 */
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

/**
 * @brief Performs the DDA algorithm for a given ray.
 * @param cub The game structure.
 * @param ray The ray structure containing the ray's information.
 * @param is_open A boolean indicating whether or not the door is open.
 * @return Updated ray structure after performing the DDA algorithm.
 * The DDA algorithm is used to calculate which wall is hit by the ray. It is
 * used in the raycasting algorithm for rendering the game's 3D view.
 */
t_ray	perform_dda(t_cub *cub, t_ray ray, t_bool is_open)
{
	while (1)
	{
		if (ray.map_x < 0 || ray.map_x >= cub->player.map_width
			|| ray.map_y < 0 || ray.map_y >= cub->player.map_height)
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
			|| cub->map[ray.map_y][ray.map_x] == 'D'
			|| (cub->map[ray.map_y][ray.map_x] == '2' && !is_open))
			break ;
	}
	return (ray);
}

/**
 * @brief Calculates the height of the wall to be drawn.
 * @param ray The ray structure containing the ray's information.
 * @return Updated ray structure with line height.
 * Calculates wall height for drawing based on perpendicular wall distance.
 */
static t_ray	calculate_wall_heigh(t_ray ray)
{
	if (ray.side == 0 && ray.ray_dir_x != 0)
		ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
	else if (ray.ray_dir_y != 0)
		ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
	ray.line_height = (int)(WIN_HEIGHT / ray.perp_wall_dist);
	return (ray);
}

/**
 * @brief Renders walls and floor on the screen.
 * Casts rays for each screen column, drawing walls and floor.
 * Rays advance on the map until hitting a wall; distance is calculated
 * for correct wall height rendering.
 * @param cub The game data structure.
 */
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
}
