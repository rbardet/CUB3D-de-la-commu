/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:51:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 15:32:29 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move(t_cub *cub, int key)
{
	if (key == XK_w)
	{
		cub->player.pos_x += cub->player.dir_x * MOVE_SPEED;
		cub->player.pos_y += cub->player.dir_y * MOVE_SPEED;
	}
	else if (key == XK_s)
	{
		cub->player.pos_x -= cub->player.dir_x * MOVE_SPEED;
		cub->player.pos_y -= cub->player.dir_y * MOVE_SPEED;
	}
	else if (key == XK_a)
	{
		cub->player.pos_x += cub->player.dir_y * MOVE_SPEED;
		cub->player.pos_y += cub->player.dir_x * MOVE_SPEED;
	}
	else if (key == XK_d)
	{
		cub->player.pos_x -= cub->player.dir_y * MOVE_SPEED;
		cub->player.pos_y -= cub->player.dir_x * MOVE_SPEED;
	}
	raycast(cub);
}

void	rotate_right(t_cub *cub)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(-ROT_SPEED)
		- cub->player.dir_y * sin(-ROT_SPEED);
	cub->player.dir_y = old_dirx * sin(-ROT_SPEED)
		+ cub->player.dir_y * cos(-ROT_SPEED);
	old_planex = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(-ROT_SPEED)
		- cub->player.plane_y * sin(-ROT_SPEED);
	cub->player.plane_y = old_planex * sin(-ROT_SPEED)
		+ cub->player.plane_y * cos(-ROT_SPEED);
	raycast(cub);
}

void	rotate_left(t_cub *cub)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(ROT_SPEED)
		- cub->player.dir_y * sin(ROT_SPEED);
	cub->player.dir_y = old_dirx * sin(ROT_SPEED)
		+ cub->player.dir_y * cos(ROT_SPEED);
	old_planex = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x
		* cos(ROT_SPEED) - cub->player.plane_y * sin(ROT_SPEED);
	cub->player.plane_y = old_planex * sin(ROT_SPEED)
		+ cub->player.plane_y * cos(ROT_SPEED);
	raycast(cub);
}
