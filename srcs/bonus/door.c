/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:49:51 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/01 06:50:07 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_bool	is_next_to_door(t_cub *cub)
{
	if (cub->map[(int)cub->player.pos_y + 1][(int)cub->player.pos_x] == 'D'
		|| cub->map[(int)cub->player.pos_y - 1][(int)cub->player.pos_x] == 'D'
		|| cub->map[(int)cub->player.pos_y][(int)cub->player.pos_x + 1] == 'D'
		|| cub->map[(int)cub->player.pos_y][(int)cub->player.pos_x - 1] == 'D'
		|| cub->map[(int)cub->player.pos_y + 1][(int)cub->player.pos_x] == '2'
		|| cub->map[(int)cub->player.pos_y - 1][(int)cub->player.pos_x] == '2'
		|| cub->map[(int)cub->player.pos_y][(int)cub->player.pos_x + 1] == '2'
		|| cub->map[(int)cub->player.pos_y][(int)cub->player.pos_x - 1] == '2')
		return (TRUE);
	return (FALSE);
}

static t_bool	open_door(t_cub *cub)
{
	t_ray	ray;
	int		x;

	x = WIN_WIDTH / 2;
	ray = init_ray(cub, x);
	ray = ray_dist_x(cub, ray);
	ray = ray_dist_y(cub, ray);
	ray = perform_dda(cub, ray, FALSE);
	if ((cub->map[ray.map_y][ray.map_x] == 'D'
		|| cub->map[ray.map_y][ray.map_x] == '2') && is_next_to_door(cub))
	{
		if (cub->map[ray.map_y][ray.map_x] == 'D')
			cub->map[ray.map_y][ray.map_x] = '2';
		else
			cub->map[ray.map_y][ray.map_x] = 'D';
		return (TRUE);
	}
	return (FALSE);
}

void	key_press(mlx_key_data_t key, void *param)
{
	t_bool	move;
	t_cub	*cub;

	cub = (t_cub *)param;
	move = false;
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
		move = open_door(cub);
	if (move)
		raycast(cub);
}
