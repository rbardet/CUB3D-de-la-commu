/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:19:38 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/25 22:28:17 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>
#include <stdio.h>

void	putPixel(int x, int y, t_rgb color, t_cub *cub)
{
	int	pixelIndex;

	if (x >= 0 && x < cub->win_width && y >= 0 && y < cub->win_height)
	{
		// Calculer l'adresse du pixel à l'emplacement (x, y) dans le buffer
		pixelIndex = (y * cub->win_width + x) * 4; // 4 bytes par pixel (RGBA)
		cub->img.addr[pixelIndex] = color.blue;
		cub->img.addr[pixelIndex + 1] = color.green;
		cub->img.addr[pixelIndex + 2] = color.red;
	}
}

void	verLine(int x, int drawStart, int drawEnd, t_rgb color, t_cub *cub)
{
	int	y;

	// Limiter les valeurs de y pour éviter de dépasser la taille de l'écran
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= cub->win_height)
		drawEnd = cub->win_height - 1;
	// Initialiser le compteur pour les pixels à dessiner
	y = drawStart;
	// Dessiner les pixels avec une boucle while
	while (y <= drawEnd)
	{
		putPixel(x, y, color, cub); // Dessiner le pixel à la position (x, y)
		y++;                        // Passer au pixel suivant
	}
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color, t_cub *cub)
{
    char *dst;

    // Check bounds to prevent segfaults
    if (x < 0 || x >= cub->win_width || y < 0 || y >= cub->win_height)
        return;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}


// In raycast.c or wherever your raycast function is defined
void	raycast(t_cub *cub)
{
	int		x;
	int		y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
		double side_dist_x;
		double side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
		double perp_wall_dist;
		int step_x;
		int step_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		ceil_color;
	int		floor_color;

	x = 0;
	while (x < cub->win_width)
	{
		// Calculate ray position and direction
		double camera_x = 2 * x / (double)cub->win_width - 1;
			// x-coordinate in camera space
		ray_dir_x = cub->player.dir_x + cub->player.plane_x * camera_x;
		ray_dir_y = cub->player.dir_y + cub->player.plane_y * camera_x;
		// Which box of the map we're in
		map_x = (int)cub->player.pos_x;
		map_y = (int)cub->player.pos_y;
		// Length of ray from current position to next x or y-side
		// Length of ray from one x or y-side to next x or y-side
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		// What direction to step in x or y direction (either +1 or -1)
		int hit = 0; // Was a wall hit?
		int side;    // Was a NS or a EW wall hit?
		// Calculate step and initial sideDist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (cub->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - cub->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (cub->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - cub->player.pos_y) * delta_dist_y;
		}
		// Perform DDA (Digital Differential Analysis)
		while (hit == 0)
		{
			// Jump to next map square, either in x-direction, or in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			// Check if ray has hit a wall
			if (cub->map[map_x][map_y] == '1')
				hit = 1;
		}
		// Calculate distance projected on camera direction
		if (side == 0)
			perp_wall_dist = (map_x - cub->player.pos_x + (1 - step_x) / 2)
				/ ray_dir_x;
		else
			perp_wall_dist = (map_y - cub->player.pos_y + (1 - step_y) / 2)
				/ ray_dir_y;
		// Calculate height of line to draw on screen
		line_height = (int)(cub->win_height / perp_wall_dist);
		// Calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_height / 2 + cub->win_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + cub->win_height / 2;
		if (draw_end >= cub->win_height)
			draw_end = cub->win_height - 1;
		// Draw ceiling
		ceil_color = (cub->ceil.red << 16) | (cub->ceil.green << 8) | cub->ceil.blue;
		y = 0;
		while (y < draw_start)
		{
			my_mlx_pixel_put(&cub->img, x, y, ceil_color, cub);
			y++;
		}
		// Draw floor
		floor_color = (cub->floor.red << 16) | (cub->floor.green << 8) | cub->floor.blue;
		y = draw_end;
		while (y < cub->win_height)
		{
			my_mlx_pixel_put(&cub->img, x, y, floor_color, cub);
			y++;
		}
		// Here you would draw the wall texture between draw_start and draw_end
		// ...
		x++;
	}
	mlx_put_image_to_window(cub->init_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
}
