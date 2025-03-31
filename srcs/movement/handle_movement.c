/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:36 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 23:42:49 by throbert         ###   ########.fr       */
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
	static int	center_x = WIN_WIDTH / 2;
	static int	center_y = WIN_HEIGHT / 2;
	int			mouse_x;
	int			mouse_y;
	double		delta_x;
	t_cub		*cub;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_ESCAPE))
	{
		free_struct(cub);
		return ;
	}
	mlx_get_mouse_pos(cub->init_ptr, &mouse_x, &mouse_y);
	delta_x = mouse_x - center_x;
	if (delta_x)
	{
		rotate_view(cub, delta_x * -MOUSE_SENSITIVITY);
		raycast(cub);
	}
	mlx_set_mouse_pos(cub->init_ptr, center_x, center_y);
	if (is_valid_move(cub))
		raycast(cub);
}


