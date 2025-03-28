/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:48:34 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 15:59:36 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Free all mlx structs and exit the program.
 * @param cub the t_cub struct containing the game state.
 */
void	free_struct(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->img_ptr)
		mlx_delete_image(cub->init_ptr, cub->img_ptr);
	if (cub->no_xpm)
		mlx_delete_texture(cub->no_xpm);
	if (cub->ea_xpm)
		mlx_delete_texture(cub->ea_xpm);
	if (cub->so_xpm)
		mlx_delete_texture(cub->so_xpm);
	if (cub->we_xpm)
		mlx_delete_texture(cub->we_xpm);
	if (cub->do_xpm)
		mlx_delete_texture(cub->do_xpm);
	if (cub->init_ptr)
		mlx_terminate(cub->init_ptr);
	if (cub->map)
		free_tab(cub->map);
	free(cub);
	exit (0);
}

/**
 * Handles all the key press event.
 * @param key		The key that was pressed.
 * @param cub		The main struct of the project.
 * @return			Always 0.
*/
static void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		free_struct(cub);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
		move_frontback(cub, keydata.key);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		move_side(cub, keydata.key);
	else if (keydata.key == MLX_KEY_LEFT)
		rotate_left(cub);
	else if (keydata.key == MLX_KEY_RIGHT)
		rotate_right(cub);
}

/**
 * @brief Open a window and start the mlx event loop.
 * @param cub the t_cub struct containing the game state.
 */
void	open_window(t_cub *cub)
{
	cub->img_ptr = mlx_new_image(cub->init_ptr,
			cub->win_width, cub->win_height);
	if (!cub->img_ptr)
	{
		free_struct(cub);
		return ;
	}
	mlx_image_to_window(cub->init_ptr, cub->img_ptr, 0, 0);
	raycast(cub);
	mlx_key_hook(cub->init_ptr, handle_keypress, cub);
	mlx_close_hook(cub->init_ptr, free_struct, cub);
	mlx_loop(cub->init_ptr);
}
