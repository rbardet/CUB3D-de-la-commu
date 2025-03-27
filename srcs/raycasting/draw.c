/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:08:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 23:05:53 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// get the starting point of the drawing and the end point
void	get_draw_size(t_cub *cub)
{
	cub->raycast.draw_start = -cub->raycast.line_height / 2 + WIN_HEIGHT / 2;
	if (cub->raycast.draw_start < 0)
		cub->raycast.draw_start = 0;
	cub->raycast.draw_end = cub->raycast.line_height / 2 + WIN_HEIGHT / 2;
	if (cub->raycast.draw_end >= WIN_HEIGHT)
		cub->raycast.draw_end = WIN_HEIGHT - 1;
}

// Fonction pour obtenir la couleur d'un pixel dans la texture
int get_texture_color(t_img *texture, int texX, int texY)
{
	int pixelIndex = texY * texture->line_len + texX * (texture->bpp / 8);
	int color = *(int *)(texture->addr + pixelIndex);  // Extraire la couleur
	return color;
}

void draw_wall(t_cub *cub, int x)
{
	int texNum;  // Numéro de la texture (0: Nord, 1: Sud, 2: Est, 3: Ouest)
	double wallX;
	int texX, texY;
	double step, texPos;
	int color;

	// Déterminer la texture en fonction du côté du mur
	if (cub->raycast.side == 0 && cub->raycast.ray_dir_x > 0)
		texNum = 2;  // Est
	else if (cub->raycast.side == 0 && cub->raycast.ray_dir_x < 0)
		texNum = 3;  // Ouest
	else if (cub->raycast.side == 1 && cub->raycast.ray_dir_y > 0)
		texNum = 1;  // Sud
	else
		texNum = 0;  // Nord

	// Calculer la position exacte du rayon sur le mur
	if (cub->raycast.side == 0)
		wallX = cub->player.pos_y + cub->raycast.perp_wall_dist * cub->raycast.ray_dir_y;
	else
		wallX = cub->player.pos_x + cub->raycast.perp_wall_dist * cub->raycast.ray_dir_x;
	wallX -= floor(wallX);

	// Calculer la coordonnée x de la texture
	texX = (int)(wallX * cub->img[texNum]->line_len / (cub->img[texNum]->bpp / 8));
	if ((cub->raycast.side == 0 && cub->raycast.ray_dir_x > 0) || (cub->raycast.side == 1 && cub->raycast.ray_dir_y < 0))
		texX = (cub->img[texNum]->line_len / (cub->img[texNum]->bpp / 8)) - texX - 1;

	// Calculer la quantité à incrémenter pour chaque pixel de l'écran
	step = 1.0 * cub->img[texNum]->line_len / (cub->img[texNum]->bpp / 8) / (cub->raycast.draw_end - cub->raycast.draw_start);
	texPos = (cub->raycast.draw_start - cub->win_height / 2 + (cub->raycast.draw_end - cub->raycast.draw_start) / 2) * step;

	for (int y = cub->raycast.draw_start; y < cub->raycast.draw_end; y++)
	{
		texY = (int)texPos & ((cub->img[texNum]->line_len / (cub->img[texNum]->bpp / 8)) - 1);
		texPos += step;
		color = get_texture_color(cub->img[texNum], texX, texY);
		if (cub->raycast.side == 1)  // Assombrir les murs Nord et Sud
			color = (color >> 1) & 8355711;
		mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y, color);
	}
}


void	draw_vertical_line(t_cub *cub, int x)
{
	int	y;

	if (cub->raycast.side == 1)
		cub->raycast.color = 0xAAAAAA;
	else
		cub->raycast.color = 0xFFFFFF;
	y = cub->raycast.draw_start;
	while (y <= cub->raycast.draw_end)
	{
		mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y, cub->raycast.color);
		y++;
	}
}

// draw the ceilling in the first half of the screen using :
// cub->ceilling.red;
// cub->ceilling.green;
// cub->ceilling.blie;
void	draw_ceilling(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y,
				(cub->ceil.red << 16) | (cub->ceil.green << 8)
				| cub->ceil.blue);
			x++;
		}
		y++;
	}
}

// draw the floor in the second half of the screen using :
// cub->floor.red;
// cub->floor.green;
// cub->floor.blie;
void	draw_floor(t_cub *cub)
{
	int	y;
	int	x;

	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y,
				(cub->floor.red << 16) | (cub->floor.green << 8)
				| cub->floor.blue);
			x++;
		}
		y++;
	}
}
