/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:19:38 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/25 22:06:17 by rbardet-         ###   ########.fr       */
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
		// Calculer l'adresse du pixel à l'emplacement (x, y) dans le buffer
		pixelIndex = (y * cub->win_width + x) * 4; // 4 bytes par pixel (RGBA)

		cub->img.addr[pixelIndex] = color.blue;
		cub->img.addr[pixelIndex + 1] = color.green;
		cub->img.addr[pixelIndex + 2] = color.red;
	}
}

void verLine(int x, int drawStart, int drawEnd, t_rgb color, t_cub *cub)
{
	int y;
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
		y++;  // Passer au pixel suivant
	}
}

int raycast(t_cub *cub)
{
	int x;
	double cameraX;
	double rayDirX;
	double rayDirY;
	double posX;
	double posY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	int side;
	int hit;
	int lineHeight;
	int drawStart;
	int drawEnd;
	t_rgb color;

	hit = 0;  // Initialize hit
	x = 0;    // Initialize x
	posX = cub->player.pos_x;
	posY = cub->player.pos_y;

	while (x < cub->win_width) // Loop for the entire screen width
	{
		cameraX = 2 * x / (double)cub->win_width - 1;
		rayDirX = cub->player.dir_x + cub->player.plane_x * cameraX;
		rayDirY = cub->player.dir_y + cub->player.plane_y * cameraX;
		mapX = (int)posX;
		mapY = (int)posY;

		deltaDistX = fabs(1.0 / rayDirX);
		deltaDistY = fabs(1.0 / rayDirY);


		// Set steps and sideDist for ray direction
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		// Debugging prints: Display ray parameters
		printf("Ray %d: posX = %f, posY = %f\n", x, posX, posY);
		printf("Ray %d: rayDirX = %f, rayDirY = %f\n", x, rayDirX, rayDirY);
		printf("Ray %d: mapX = %d, mapY = %d\n", x, mapX, mapY);
		printf("Ray %d: sideDistX = %f, sideDistY = %f\n", x, sideDistX, sideDistY);

		hit = 0;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0; // X direction (horizontal)
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1; // Y direction (vertical)
			}

			if (cub->map[mapX][mapY] > 0)
				hit = 1;
		}

		// Calculate perpendicular wall distance and debug
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		printf("Ray %d: perpWallDist = %f\n", x, perpWallDist);

		lineHeight = (int)(cub->win_height / perpWallDist);

		drawStart = -lineHeight / 2 + cub->win_height / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + cub->win_height / 2;
		if (drawEnd >= cub->win_height)
			drawEnd = cub->win_height - 1;

		if (side == 0)
			color = (t_rgb){0, 120, 131};
		else
			color = (t_rgb){43, 174, 90};
		verLine(x, drawStart, drawEnd, color, cub);
		x++;
	}

	mlx_put_image_to_window(cub->init_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
	return (0);
}
