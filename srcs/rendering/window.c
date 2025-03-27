/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:48:34 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 22:29:31 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_img(t_img **img)
{
	int	i;

	i = 0;
	if (!img)
		return ;
	while (i != 5)
	{
		if (!img[i])
			return ;
		free(img[i]);
		img[i] = NULL;
		i++;
	}
	free(img);
	img = NULL;
}

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
	if (cub->img)
		free_img(cub->img);
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
	else if (key == XK_w || key == XK_s)
		move_frontback(cub, key);
	else if (key == XK_a || key == XK_d)
		move_side(cub, key);
	else if (key == XK_Left)
		rotate_left(cub);
	else if (key == XK_Right)
		rotate_right(cub);
	return (0);
}

// load every texture pixel per pixel with mlx_get_data_addr
void load_texture(t_cub *cub)
{
	cub->img = malloc(sizeof(t_img *) * 5);
	if (!cub->img)
		return;
	for (int i = 0; i < 5; i++)
	{
		cub->img[i] = malloc(sizeof(t_img));
		if (!cub->img[i])
			return;
	}
	cub->img[0]->img = cub->no_xpm;
	cub->img[1]->img = cub->so_xpm;
	cub->img[2]->img = cub->ea_xpm;
	cub->img[3]->img = cub->we_xpm;
	cub->img[4]->img = cub->do_xpm;

	for (int i = 0; i < 5; i++)
	{
		cub->img[i]->addr = mlx_get_data_addr(cub->img[i]->img, &cub->img[i]->bpp,
											  &cub->img[i]->line_len, &cub->img[i]->endian);
	}
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
		free_struct(cub);
		return ;
	}
	load_texture(cub);
	if (!cub->img || !cub->img[0] || !cub->img[1]
		|| !cub->img[2] || !cub->img[3] || !cub->img[4])
	{
		ft_putstr_fd("Error\nCouldn't load texture", 2);
		free_struct(cub);
		return ;
	}
	cub->img_ptr = mlx_new_image(cub->init_ptr, cub->win_width, cub->win_height);
	if (!cub->img_ptr)
	{
		free_struct(cub);
		return ;
	}
	mlx_put_image_to_window(cub->init_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
	raycast(cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, &handle_keypress, cub);
	mlx_hook(cub->win_ptr, 17, 0, (int (*)())free_struct, cub);
	mlx_loop(cub->init_ptr);
	return ;
}
