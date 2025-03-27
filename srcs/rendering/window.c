/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:48:34 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 14:57:55 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Free all mlx structs and exit the program.
 * @param cub the t_cub struct containing the game state.
 */
int	free_struct(t_cub *cub)
{
	if (cub->no_xpm)
		mlx_destroy_image(cub->init_ptr, cub->no_xpm);
	if (cub->ea_xpm)
		mlx_destroy_image(cub->init_ptr, cub->ea_xpm);
	if (cub->so_xpm)
		mlx_destroy_image(cub->init_ptr, cub->so_xpm);
	if (cub->we_xpm)
		mlx_destroy_image(cub->init_ptr, cub->we_xpm);
	if (cub->do_xpm)
		mlx_destroy_image(cub->init_ptr, cub->do_xpm);
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
	exit(0);
}

/**
 * Handles all the key press event.
 * @param key		The key that was pressed.
 * @param cub		The main struct of the project.
 * @return			Always 0.
*/
int	handle_keypress(int key, t_cub *cub)
{
	if (key == XK_Escape)
		free_struct(cub);
	else if (key == XK_w || key == XK_s || key == XK_a || key == XK_d)
		move(cub, key);
	else if (key == XK_Left)
		rotate_left(cub);
	else if (key == XK_Right)
		rotate_right(cub);
	return (0);
}

/**
 * @brief Open a window and start the mlx event loop.
 * @param cub the t_cub struct containing the game state.
 */
void	open_window(t_cub *cub)
{
	cub->win_ptr = mlx_new_window(cub->init_ptr, cub->win_width,
			cub->win_height, "cub3d");
	if (!cub->win_ptr)
	{
		ft_putstr_fd("Error\nCouldn't create the windowd\n", 2);
		mlx_destroy_window(cub->init_ptr, cub->win_ptr);
		mlx_destroy_display(cub->init_ptr);
		free(cub->init_ptr);
		return ;
	}
	raycast(cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, &handle_keypress, cub);
	mlx_hook(cub->win_ptr, 17, 0, (int (*)())free_struct, cub);
	mlx_loop(cub->init_ptr);
	return ;
}
