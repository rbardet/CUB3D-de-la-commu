/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:08:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/30 19:41:42 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Return the correct texture of the wall hit by the ray.
 * @param ray The ray structure containing the ray's information.
 * @param cub The game structure containing all the game's data.
 * @return The texture of the wall hit by the ray.
 */
static mlx_texture_t	*get_wall_text(t_ray ray, t_cub *cub)
{
	if (cub->map[ray.map_y][ray.map_x] == 'D')
		return (cub->do_xpm);
	else if (ray.side == 1 && ray.ray_dir_y < 0)
		return (cub->no_xpm);
	else if (ray.side == 1 && ray.ray_dir_y > 0)
		return (cub->so_xpm);
	else if (ray.side == 0 && ray.ray_dir_x > 0)
		return (cub->ea_xpm);
	else
		return (cub->we_xpm);
}

/**
 * @brief Calculate the parameters necessary for drawing the wall texture.
 * @param cub The game structure containing all the game's data.
 * @param ray The ray structure containing the ray's information.
 * @param draw Parameters for texture drawing.
 * @param texture Texture to be drawn.
 */
static void	calculate_texture_params(t_cub *cub, t_ray ray,
	t_draw *draw, mlx_texture_t *texture)
{
	int	tex_width;

	if (ray.side == 0)
		draw->wall_x = cub->player.pos_y + ray.perp_wall_dist * ray.ray_dir_y;
	else
		draw->wall_x = cub->player.pos_x + ray.perp_wall_dist * ray.ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
	tex_width = texture->width;
	draw->tex_x = (int)(draw->wall_x * tex_width);
	if ((ray.side == 0 && ray.ray_dir_x > 0)
		|| (ray.side == 1 && ray.ray_dir_y < 0))
		draw->tex_x = tex_width - draw->tex_x - 1;
	if (ray.draw_end - ray.draw_start != 0)
		draw->step = 1.0 * texture->height / (ray.draw_end - ray.draw_start);
	else
		draw->step = 0;
	draw->tex_pos = (ray.draw_start - cub->win_height / 2
			+ (ray.draw_end - ray.draw_start) / 2) * draw->step;
}

/**
 * @brief Draw a wall on the screen.
 * @param cub The game structure containing all the game's data.
 * @param x The x-coordinate of the wall on the screen.
 * @param ray The ray structure containing the ray's information.
 * Draws a wall on the screen with the given x-coordinate and ray information.
 */
void	draw_wall(t_cub *cub, int x, t_ray ray)
{
	t_draw			draw;
	mlx_texture_t	*texture;
	int				y;

	texture = get_wall_text(ray, cub);
	calculate_texture_params(cub, ray, &draw, texture);
	y = ray.draw_start;
	while (y < ray.draw_end)
	{
		draw.tex_y = (int)draw.tex_pos % (texture->height);
		draw.tex_pos += draw.step;
		draw.color = get_texture_color(texture, draw.tex_x, draw.tex_y);
		mlx_put_pixel(cub->img_ptr, x, y, draw.color);
		y++;
	}
}

/**
 * @brief Draw the ceiling in the first half of the screen.
 * @param cub The game structure containing all the game's data.
 */
void	draw_ceilling(t_cub *cub)
{
	int			y;
	int			x;
	int32_t		color;

	color = (cub->ceil.red << 16) | (cub->ceil.green << 8) | cub->ceil.blue;
	y = -1;
	while (++y < WIN_HEIGHT / 2)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			mlx_put_pixel(cub->img_ptr, x, y, color);
	}
}

/**
 * @brief Draw the floor in the second half of the screen.
 * @param cub The game structure containing all the game's data.
 */
void	draw_floor(t_cub *cub)
{
	int			y;
	int			x;
	int32_t		color;

	color = (cub->floor.red << 16) | (cub->floor.green << 8) | cub->floor.blue;
	y = WIN_HEIGHT / 2 -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			mlx_put_pixel(cub->img_ptr, x, y, color);
	}
}
