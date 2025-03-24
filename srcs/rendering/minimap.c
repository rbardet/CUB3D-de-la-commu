/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:10:20 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/24 22:43:32 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			mlx_pixel_put(cub->init_ptr, cub->win_ptr, cub->win_width - i, cub->win_height - j, 0xFF0000);
			j++;
		}
		i++;
	}
	return ;
}

int	minimap(t_cub *cub)
{
	if (!cub || !cub->init_ptr || !cub->win_ptr)
	{
		ft_putstr_fd("Error in minimap\n", 2);
		return(1);
	}
	render_minimap(cub);
	return(0);
}
