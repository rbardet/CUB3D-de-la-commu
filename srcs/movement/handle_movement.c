/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:36 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 23:55:10 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


/**
 * Handles all the key press event.
 * @param key		The key that was pressed.
 * @param cub		The main struct of the project.
 * @return			return TRUE if a movement is detected
*/
t_bool	is_valid_move(t_cub *cub)
{
	t_bool	move;

	move = false;
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_W))
		move |= move_front(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_S))
		move |= move_back(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_A))
		move |= move_left(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_D))
		move |= move_right(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_LEFT))
		move |= rotate_left(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_RIGHT))
		move |= rotate_right(cub);
	return (move);
}

void	handle_move(void *param)
{
	t_cub	*cub;
	t_bool	move;

	move = false;
	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_ESCAPE))
		free_struct(cub);
	move |= is_valid_move(cub);
	
	if (move)
		raycast(cub);
}
