/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:36 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 22:13:26 by hdelacou         ###   ########.fr       */
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

void	checker(t_cub *cub)
{
	system("clear");
	printf("\033[36m┌───────────────────────────┐\n");
	printf("\033[36m│ \033[1mPlayer Position           \033[0;36m│\n");
	printf("\033[36m├───────────────────────────┤\n");
	printf("\033[36m│ World: \033[33mX=%6.2f \033[33mY=%6.2f  \033[36m│\n",
		cub->player.pos_x, cub->player.pos_y);
	printf("\033[36m│ Map:   \033[33mX=%3d    \033[33mY=%3d     \033[36m│\n",
		(int)cub->player.pos_x, (int)cub->player.pos_y);
	printf("\033[36m├───────────────────────────┤\n");
	printf("\033[36m│ \033[1mDirection & Plane         \033[0;36m│\n");
	printf("\033[36m├───────────────────────────┤\n");
	printf("\033[36m│ Dir:   \033[35mX=%7.4f \033[35mY=%7.4f\033[36m│\n",
		cub->player.dir_x, cub->player.dir_y);
	printf("\033[36m│ Plane: \033[35mX=%7.4f \033[35mY=%7.4f\033[36m│\n",
		cub->player.plane_x, cub->player.plane_y);
	printf("\033[36m└───────────────────────────┘\n");
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
	checkers(cub);
}
