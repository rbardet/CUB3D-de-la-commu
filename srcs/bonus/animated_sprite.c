/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:04:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/01 05:50:10 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	animated_sprite(mouse_key_t button,
	action_t action, modifier_key_t mods, void *param)
{
	t_cub			*cub;
	int				i;

	(void)mods;
	cub = (t_cub *)param;
	i = 0;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		cub->sprite[0]->enabled = FALSE;
		while (cub->sprite[i])
		{
			mlx_image_to_window(cub->init_ptr, cub->sprite[i],
				cub->win_width / 2, cub->win_height * 0.73);
			cub->sprite[i]->enabled = FALSE;
			i++;
		}
		cub->sprite[0]->enabled = TRUE;
	}
}
