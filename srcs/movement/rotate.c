/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:15:12 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/30 19:26:48 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Rotate the player to the right.
 * @param cub Player and game data structure.
 * @return TRUE if successful.
 */
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

/**
 * @brief Rotate the player to the left.
 * @param cub Player and game data structure.
 * @return TRUE if successful.
 */
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
