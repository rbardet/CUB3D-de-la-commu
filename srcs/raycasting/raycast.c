/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:19:38 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/26 20:43:02 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>
#include <stdio.h>

void	raycast(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < cub->win_width)
	{
		double cameraX = (2 * (double)x / (double)cub->win_width) - 1;
		double	rayDirX = cub->player.dir_x + cub->player.plane_x * cameraX;
		double	rayDirY = cub->player.dir_y + cub->player.plane_y * cameraX;
		x++;
	}
}

