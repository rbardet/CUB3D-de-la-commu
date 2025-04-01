/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:08:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/01 11:42:52 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// get the index of the texture that will be drawn on screen
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

static void	calculate_texture_params(t_cub *cub, t_ray ray, t_draw *draw,
		mlx_texture_t *texture)
{
	int	tex_width;

	if (ray.side == 0)
		draw->wall_x = cub->player.pos_y + ray.perp_wall_dist * ray.ray_dir_y;
	else
		draw->wall_x = cub->player.pos_x + ray.perp_wall_dist * ray.ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
	tex_width = texture->width;
	draw->tex_x = (int)(draw->wall_x * tex_width);
	if ((ray.side == 0 && ray.ray_dir_x > 0) || (ray.side == 1
			&& ray.ray_dir_y < 0))
		draw->tex_x = tex_width - draw->tex_x - 1;
	draw->step = (double)texture->height / (double)ray.line_height;
	draw->tex_pos = (ray.draw_start - WIN_HEIGHT / 2 + ray.line_height / 2)
		* draw->step;
}

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

// draw the ceilling in the first half of the screen using :
// cub->ceilling.red;
// cub->ceilling.green;
// cub->ceilling.blue;
void	draw_ceilling(t_cub *cub)
{
	int			y;
	int			x;
	uint32_t	color;

	color = (cub->ceil.red << 24) | (cub->ceil.green << 16)
		| cub->ceil.blue << 8 | 255;
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_put_pixel(cub->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

// draw the floor in the second half of the screen using :
// cub->floor.red;
// cub->floor.green;
// cub->floor.blue;
void	draw_floor(t_cub *cub)
{
	int				y;
	int				x;
	uint32_t		color;

	color = (cub->floor.red << 24) | (cub->floor.green << 16)
		| cub->floor.blue << 8 | 255;
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_put_pixel(cub->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}
