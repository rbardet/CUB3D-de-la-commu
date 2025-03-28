/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:51:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 15:11:33 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_bool	check_collision(t_cub *cub, double x, double y)
{
	if (cub->map[(int)y][(int)x] == '1')
		return (FALSE);
	return (TRUE);
}

void	move_frontback(t_cub *cub, int key)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = cub->player.pos_x;
	tmp_y = cub->player.pos_y;
	if (key == MLX_KEY_W)
	{
		cub->player.pos_x += cub->player.dir_x * MOVE_SPEED;
		cub->player.pos_y += cub->player.dir_y * MOVE_SPEED;
	}
	else if (key == MLX_KEY_S)
	{
		cub->player.pos_x -= cub->player.dir_x * MOVE_SPEED;
		cub->player.pos_y -= cub->player.dir_y * MOVE_SPEED;
	}
	if (!check_collision(cub, cub->player.pos_x, cub->player.pos_y))
	{
		cub->player.pos_x = tmp_x;
		cub->player.pos_y = tmp_y;
		return ;
	}
	raycast(cub);
}

void	move_side(t_cub *cub, int key)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = cub->player.pos_x;
	tmp_y = cub->player.pos_y;
	if (key == MLX_KEY_A)
	{
		cub->player.pos_x += cub->player.dir_y * MOVE_SPEED;
		cub->player.pos_y += cub->player.dir_x * MOVE_SPEED;
	}
	else if (key == MLX_KEY_D)
	{
		cub->player.pos_x -= cub->player.dir_y * MOVE_SPEED;
		cub->player.pos_y -= cub->player.dir_x * MOVE_SPEED;
	}
	if (!check_collision(cub, cub->player.pos_x, cub->player.pos_y))
	{
		cub->player.pos_x = tmp_x;
		cub->player.pos_y = tmp_y;
		return ;
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
