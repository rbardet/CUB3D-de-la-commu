/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:19:38 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/25 21:57:58 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>
#include <math.h>
void putPixel(int x, int y, t_rgb color, t_cub *cub)
{
	int pixelIndex;

	if (x >= 0 && x < cub->win_width && y >= 0 && y < cub->win_height)
	{
		pixelIndex = (y * cub->win_width + x) * 4;
		cub->img.addr[pixelIndex] = color.blue;
		cub->img.addr[pixelIndex + 1] = color.green;
		cub->img.addr[pixelIndex + 2] = color.red;
	}
}

void verLine(int x, int drawStart, int drawEnd, t_rgb color, t_cub *cub)
{
	if (drawStart < 0) drawStart = 0;
	if (drawEnd >= cub->win_height) drawEnd = cub->win_height - 1;

	for (int y = drawStart; y <= drawEnd; y++)
	{
		putPixel(x, y, color, cub);
	}
}

int raycast(t_cub *cub)
{
	for (int x = 0; x < cub->win_width; x++)
	{
		// Calculate ray position and direction
		double cameraX = 2 * x / (double)cub->win_width - 1;
		double rayDirX = cub->player.dir_x + cub->player.plane_x * cameraX;
		double rayDirY = cub->player.dir_y + cub->player.plane_y * cameraX;

		// Player's position with fractional part
		double posX = cub->player.pos_x;
		double posY = cub->player.pos_y;

		// Map coordinates
		int mapX = (int)posX;
		int mapY = (int)posY;

		// Calculate step and initial side distances
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		int stepX;
		int stepY;
		double sideDistX;
		double sideDistY;

		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		// DDA algorithm
		int hit = 0;
		int side;
		while (!hit)
		{
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			// Check map bounds
			if (mapX < 0 || mapX >= cub->player.map_width || mapY < 0 || mapY >= cub->player.map_height)
				break;

			// Check if ray hit a wall
			if (cub->map[mapY][mapX] > 0)  // Note: map[Y][X] instead of map[X][Y]
				hit = 1;
		}

		// Calculate perpendicular wall distance
		double perpWallDist;
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		// Prevent division by zero in line height calculation
		perpWallDist = fabs(perpWallDist) + 1e-6;

		// Calculate line height and draw limits
		int lineHeight = (int)(cub->win_height / perpWallDist);
		int drawStart = -lineHeight / 2 + cub->win_height / 2;
		drawStart = drawStart < 0 ? 0 : drawStart;
		int drawEnd = lineHeight / 2 + cub->win_height / 2;
		drawEnd = drawEnd >= cub->win_height ? cub->win_height - 1 : drawEnd;

		// Choose wall color based on side hit
		t_rgb color;
		if (side == 0)
			color = (t_rgb){0, 120, 131};  // Horizontal wall
		else
			color = (t_rgb){43, 174, 90};  // Vertical wall

		verLine(x, drawStart, drawEnd, color, cub);
	}

	mlx_put_image_to_window(cub->init_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
	return (0);
}
