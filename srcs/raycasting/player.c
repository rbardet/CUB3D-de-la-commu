/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:20:11 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/24 21:20:30 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_cub *cub)
{
	int i, j;
	for (i = 0; cub->map[i]; i++)
	{
		for (j = 0; cub->map[i][j]; j++)
		{
			if (ft_strchr("NSEW", cub->map[i][j]))
			{
				cub->player.x = j + 0.5;
				cub->player.y = i + 0.5;
				if (cub->map[i][j] == 'N')
				{
					cub->player.dir_x = 0;
					cub->player.dir_y = -1;
					cub->player.plane_x = 0.66;
					cub->player.plane_y = 0;
				}
				else if (cub->map[i][j] == 'S')
				{
					cub->player.dir_x = 0;
					cub->player.dir_y = 1;
					cub->player.plane_x = -0.66;
					cub->player.plane_y = 0;
				}
				else if (cub->map[i][j] == 'E')
				{
					cub->player.dir_x = 1;
					cub->player.dir_y = 0;
					cub->player.plane_x = 0;
					cub->player.plane_y = 0.66;
				}
				else if (cub->map[i][j] == 'W')
				{
					cub->player.dir_x = -1;
					cub->player.dir_y = 0;
					cub->player.plane_x = 0;
					cub->player.plane_y = -0.66;
				}
				return ;
			}
		}
	}
}

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
