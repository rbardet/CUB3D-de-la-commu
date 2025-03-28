/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:15:12 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 20:15:43 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_bool	rotate_right(t_cub *cub)
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
	return (TRUE);
}

t_bool	rotate_left(t_cub *cub)
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
	return (TRUE);
}
