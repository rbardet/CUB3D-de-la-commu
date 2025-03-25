/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:19:38 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/25 17:23:43 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*init_image(t_cub *cub)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	img->ptr = mlx_new_image(cub->init_ptr, cub->win_width, cub->win_height);
	if (!img->ptr)
	{
		printf("Erreur : Impossible de créer l'image MiniLibX\n");
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_length, &img->endian);
	return (img);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color, t_cub *cub)
{
	int	pixel;

	if (x >= 0 && x < cub->win_width && y >= 0 && y < cub->win_height)
	{
		pixel = (y * img->line_length) + (x * (img->bpp / 8));
		*(int *)(img->addr + pixel) = color;
	}
}

int raycast(t_cub *cub)
{
	for (int x = 0; x < cub->win_width; x++)
	{
		double cameraX = 2 * x / (double)cub->win_width - 1;
		double rayDirX = cub->player.dir_x + cub->player.plane_x * cameraX;
		double rayDirY = cub->player.dir_y + cub->player.plane_y * cameraX;
		int mapX = (int)cub->player.pos_x;
		int mapY = (int)cub->player.pos_y;
		double sideDistX, sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
		int stepX = (rayDirX < 0) ? -1 : 1;
		int stepY = (rayDirY < 0) ? -1 : 1;
		if (rayDirX < 0)
			sideDistX = (cub->player.pos_x - mapX) * deltaDistX;
		else
			sideDistX = (mapX + 1.0 - cub->player.pos_x) * deltaDistX;
		if (rayDirY < 0)
			sideDistY = (cub->player.pos_y - mapY) * deltaDistY;
		else
			sideDistY = (mapY + 1.0 - cub->player.pos_y) * deltaDistY;

		int hit = 0, side;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (cub->map[mapY][mapX] > 0) hit = 1;
		}
		perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);
		int lineHeight = (int)(cub->win_height / perpWallDist);
		int drawStart = -lineHeight / 2 + cub->win_height / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + cub->win_height / 2;
		if (drawEnd >= cub->win_height) drawEnd = cub->win_height - 1;
		int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;
		for (int y = drawStart; y <= drawEnd; y++)
			my_mlx_pixel_put(cub->img, x, y, color, cub);
	}
	// Ajout de l'affichage de l'image
	mlx_put_image_to_window(cub->init_ptr, cub->win_ptr, cub->img->ptr, 0, 0);

	return (0);
}

