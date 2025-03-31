/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:15:12 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 23:34:18 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_view(t_cub *cub, double angle)
{
	double	old_dirx;
	double	old_planex;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dirx = cub->player.dir_x;
	cub->player.dir_x = old_dirx * cos_a - cub->player.dir_y * sin_a;
	cub->player.dir_y = old_dirx * sin_a + cub->player.dir_y * cos_a;
	old_planex = cub->player.plane_x;
	cub->player.plane_x = old_planex * cos_a - cub->player.plane_y * sin_a;
	cub->player.plane_y = old_planex * sin_a + cub->player.plane_y * cos_a;
}

t_bool	rotate_right(t_cub *cub)
{
	rotate_view(cub, -ROT_SPEED);
	return (TRUE);
}

t_bool	rotate_left(t_cub *cub)
{
	rotate_view(cub, ROT_SPEED);
	return (TRUE);
}
