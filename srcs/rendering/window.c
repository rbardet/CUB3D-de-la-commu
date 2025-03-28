/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:48:34 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 19:38:49 by rbardet-         ###   ########.fr       */
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
 * @return			return TRUE if a movement is detected
*/
static t_bool	is_valid_move(t_cub *cub)
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

static void	handle_move(void *param)
{
	t_cub	*cub;
	bool	move;

	move = false;
	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->init_ptr, MLX_KEY_ESCAPE))
		free_struct(cub);
	move |= is_valid_move(cub);
	if (move)
		raycast(cub);
}

/**
 * @brief Open a window and start the mlx event loop.
 * @param cub the t_cub struct containing the game state.
 */
void	open_window(t_cub *cub)
{
	cub->img_ptr = mlx_new_image(cub->init_ptr, cub->win_width, cub->win_height);
	if (!cub->img_ptr)
	{
		free_struct(cub);
		return ;
	}
	mlx_image_to_window(cub->init_ptr, cub->img_ptr, 0, 0);
	raycast(cub);
	mlx_loop_hook(cub->init_ptr, handle_move, cub);
	mlx_close_hook(cub->init_ptr, free_struct, cub);
	mlx_loop(cub->init_ptr);
}
