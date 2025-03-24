/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:48:34 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/24 21:06:43 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// function used to free the main struct of the project
int	free_struct(t_cub *cub)
{
	if (cub->init_ptr && cub->win_ptr)
		mlx_destroy_window(cub->init_ptr, cub->win_ptr);
	if (cub->init_ptr)
		mlx_destroy_display(cub->init_ptr);
	if (cub->init_ptr)
		free(cub->init_ptr);
	if (cub->map)
		free_tab(cub->map);
	if (cub)
		free(cub);
	exit (0);
}

// check the keypressed to see wich action need to be done
int	handle_keypress(int key, t_cub *cub)
{
	if (key == XK_Escape)
		free_struct(cub);
	return (0);
}

// open the a window with the size defined in the Header
void	open_window(t_cub *cub)
{
	cub->win_ptr = mlx_new_window(cub->init_ptr, cub->win_height,
			cub->win_width, "cub3d");
	if (!cub->win_ptr)
	{
		ft_putstr_fd("Error\nCouldn't create the windowd\n", 2);
		mlx_destroy_window(cub->init_ptr, cub->win_ptr);
		mlx_destroy_display(cub->init_ptr);
		free(cub->init_ptr);
		return ;
	}
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, &handle_keypress, cub);
	mlx_hook(cub->win_ptr, 17, 0, free_struct, cub);
	mlx_loop(cub->init_ptr);
	return ;
}
