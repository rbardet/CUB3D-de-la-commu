/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:20:11 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/24 22:38:41 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_keypress(int key, t_cub *cub)
{
	double	move_speed;

	move_speed = 0.1;
	if (key == XK_w)
	{
		if (cub->map[(int)(cub->player.y)][(int)(cub->player.x
				+ cub->player.dir_x * move_speed)] != '1')
			cub->player.x += cub->player.dir_x * move_speed;
		if (cub->map[(int)(cub->player.y + cub->player.dir_y
				* move_speed)][(int)(cub->player.x)] != '1')
			cub->player.y += cub->player.dir_y * move_speed;
	}
	else if (key == XK_s)
	{
		if (cub->map[(int)(cub->player.y)][(int)(cub->player.x
				- cub->player.dir_x * move_speed)] != '1')
			cub->player.x -= cub->player.dir_x * move_speed;
		if (cub->map[(int)(cub->player.y - cub->player.dir_y
				* move_speed)][(int)(cub->player.x)] != '1')
			cub->player.y -= cub->player.dir_y * move_speed;
	}
	raycast(cub);
	return (0);
}
