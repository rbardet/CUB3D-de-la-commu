/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_press.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:52:47 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/01 00:56:49 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	key_press(mlx_key_data_t key, void *param)
{
	t_bool	move;
	t_cub	*cub;

	cub = (t_cub *)param;
	move = false;
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
		move = open_door(cub);
	if (key.key == MLX_MOUSE_BUTTON_LEFT && key.action == MLX_PRESS)
		animated_sprite(cub);
	if (move)
		raycast(cub);
}
