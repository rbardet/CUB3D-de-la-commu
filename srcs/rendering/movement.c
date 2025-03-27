/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:51:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 13:15:59 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void move_forward(t_cub *cub)
{
	cub->player.pos_x += cub->player.dir_x * MOVE_SPEED;
	cub->player.pos_y += cub->player.dir_y * MOVE_SPEED;
	raycast(cub);
}

void move_backward(t_cub *cub)
{
	cub->player.pos_x -= cub->player.dir_x * MOVE_SPEED;
	cub->player.pos_y -= cub->player.dir_y * MOVE_SPEED;
	raycast(cub);
}

void move_left(t_cub *cub)
{
	// Calcul du vecteur perpendiculaire à la direction
	double perp_x = -cub->player.dir_y;
	double perp_y = cub->player.dir_x;

	cub->player.pos_x += perp_x * MOVE_SPEED;
	cub->player.pos_y += perp_y * MOVE_SPEED;
	raycast(cub);
}

void move_right(t_cub *cub)
{
	double perp_x = cub->player.dir_y;
	double perp_y = -cub->player.dir_x;

	cub->player.pos_x += perp_x * MOVE_SPEED;
	cub->player.pos_y += perp_y * MOVE_SPEED;
	raycast(cub);
}

void rotate_right(t_cub *cub)
{
	double oldDirX = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(-ROT_SPEED) - cub->player.dir_y * sin(-ROT_SPEED);
	cub->player.dir_y = oldDirX * sin(-ROT_SPEED) + cub->player.dir_y * cos(-ROT_SPEED);
	double oldPlaneX = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(-ROT_SPEED) - cub->player.plane_y * sin(-ROT_SPEED);
	cub->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + cub->player.plane_y * cos(-ROT_SPEED);
	raycast(cub);
}

void rotate_left(t_cub *cub)
{
	double oldDirX = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(ROT_SPEED) - cub->player.dir_y * sin(ROT_SPEED);
	cub->player.dir_y = oldDirX * sin(ROT_SPEED) + cub->player.dir_y * cos(ROT_SPEED);
	double oldPlaneX = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(ROT_SPEED) - cub->player.plane_y * sin(ROT_SPEED);
	cub->player.plane_y = oldPlaneX * sin(ROT_SPEED) + cub->player.plane_y * cos(ROT_SPEED);
	raycast(cub);
}

