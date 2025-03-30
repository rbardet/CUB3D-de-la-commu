/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:49:51 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/30 19:26:13 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * Handles the door key press event.
 * @param key  The mlx key data.
 * @param param The main game struct.
 */
void	handle_door(mlx_key_data_t key, void *param)
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

/**
 * Checks if the player is adjacent to a door ('D' or '2').
 * @param cub The main game structure containing the player and map information.
 * @return TRUE if the player is next to a door, FALSE otherwise.
 */
t_bool	is_next_to_door(t_cub *cub)
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

/**
 * Opens or closes a door.
 * @param cub The main game structure.
 * @return TRUE on success.
 */
t_bool	open_door(t_cub *cub)
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
