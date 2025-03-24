/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:10:20 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/24 21:03:55 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	minimap(t_cub *cub)
{
	if (!cub->init_ptr || !cub->win_ptr)
	{
		ft_putstr_fd("Error in minimap\n", 2);
		return ;
	}
	// mlx_pixel_put()
	return ;
}
