/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:08:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 15:24:53 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef	struct s_draw
{
	int			tex_num;
	double		wallX;
	int			texX;
	int			texY;
	double		step;
	double		texPos;
	int			color;
}				t_draw;

// get the color of the pixel inside the texture
static int get_texture_color(t_img *texture, int texX, int texY)
{
	// Vérifier que la texture et ses données sont valides
	if (!texture || !texture->texture || !texture->texture->pixels)
		return 0;

	// Vérifier que les coordonnées sont dans les limites
	if (texX < 0 || texX >= (int)texture->texture->width ||
		texY < 0 || texY >= (int)texture->texture->height)
		return 0;

	int pixel_id = (texY * texture->texture->width + texX) * 4; // 4 octets par pixel (RGBA)
	unsigned char *pixel = texture->texture->pixels + pixel_id;

	// Récupérer la couleur en format RGB (ignorer alpha)
	int color = (pixel[0] << 16) | (pixel[1] << 8) | pixel[2];

	return color;
}


// get the index of the texture that will be drawn on screen
static mlx_texture_t *get_wall_text(t_ray ray, t_cub *cub)
{
	if (ray.side == 1 && ray.ray_dir_y < 0)
		return (cub->no_xpm);
	else if (ray.side == 1 && ray.ray_dir_y > 0)
		return (cub->so_xpm);
	else if (ray.side == 0 && ray.ray_dir_x > 0)
		return (cub->ea_xpm);
	else
		return (cub->we_xpm);
}

void draw_wall(t_cub *cub, int x, t_ray ray)
{
	t_draw draw;
	t_img texture;

	// Récupération de la texture associée au rayon
	texture.texture = get_wall_text(ray, cub);

	// Calculer la position exacte du rayon sur le mur
	if (ray.side == 0)
		draw.wallX = cub->player.pos_y + ray.perp_wall_dist * ray.ray_dir_y;
	else
		draw.wallX = cub->player.pos_x + ray.perp_wall_dist * ray.ray_dir_x;
	draw.wallX -= floor(draw.wallX);

	// Calculer la coordonnée X de la texture
	int tex_width = texture.texture->width;
	draw.texX = (int)(draw.wallX * tex_width);
	if ((ray.side == 0 && ray.ray_dir_x > 0) || (ray.side == 1 && ray.ray_dir_y < 0))
		draw.texX = tex_width - draw.texX - 1;

	// Calculer la quantité à incrémenter pour chaque pixel de l'écran
	draw.step = 1.0 * texture.texture->height / (ray.draw_end - ray.draw_start);
	draw.texPos = (ray.draw_start - cub->win_height / 2 + (ray.draw_end - ray.draw_start) / 2) * draw.step;

	for (int y = ray.draw_start; y < ray.draw_end; y++)
	{
		draw.texY = (int)draw.texPos & (texture.texture->height - 1);
		draw.texPos += draw.step;

		// Obtenir la couleur de la texture
		draw.color = get_texture_color(&texture, draw.texX, draw.texY);

		if (ray.side == 1)  // Assombrir les murs Nord et Sud
			draw.color = (draw.color >> 1) & 8355711;

		// Dessiner le pixel dans l'image à l'aide de MLX42
		mlx_put_pixel(cub->img_ptr, x, y, draw.color);
	}
}


// draw the ceilling in the first half of the screen using :
// cub->ceilling.red;
// cub->ceilling.green;
// cub->ceilling.blue;
void	draw_ceilling(t_cub *cub)
{
	int	y;
	int	x;
	int	color;

	color = (cub->ceil.red << 16) | (cub->ceil.green << 8) | cub->ceil.blue;
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
	int	y;
	int	x;
	int	color;

	color = (cub->floor.red << 16) | (cub->floor.green << 8) | cub->floor.blue;
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
