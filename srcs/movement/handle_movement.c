/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:36 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/03 11:58:25 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * Handles all the key press event.
 * @param key		The key that was pressed.
 * @param cub		The main struct of the project.
 * @return			return TRUE if a movement is detected
 */
static int	is_valid_move(t_cub *cub)
{
	int	move;

	move = 0;
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_W))
		move += move_front(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_S))
		move += move_back(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_A))
		move += move_left(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_D))
		move += move_right(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_LEFT))
		move += rotate_left(cub);
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_RIGHT))
		move += rotate_right(cub);
	return (move);
}

static void	handle_mouse(t_cub *cub, int mouse_x)
{
	double	delta_x;

	delta_x = mouse_x - (WIN_WIDTH / 2);
	if (delta_x)
	{
		rotate_view(cub, delta_x * -MOUSE_SENSITIVITY);
		raycast(cub);
	}
	mlx_set_mouse_pos(cub->init_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

void	handle_move(void *param)
{
	t_cub		*cub;
	int			mouse_x;
	int			mouse_y;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_ESCAPE))
	{
		free_struct(cub);
		return ;
	}
	mlx_get_mouse_pos(cub->init_ptr, &mouse_x, &mouse_y);
	handle_mouse(cub, mouse_x);
	if (is_valid_move(cub))
		raycast(cub);
}
