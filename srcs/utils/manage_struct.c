/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:21:44 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/01 00:55:01 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_sprite(t_cub *cub)
{
	cub->sprite = malloc(sizeof(t_sprite));
	if (!cub->sprite)
		return ;
	cub->sprite->sprite1 = mlx_load_png("./graphic/Amaterasu/sprite1");
	cub->sprite->sprite2 = mlx_load_png("./graphic/Amaterasu/sprite2");
	cub->sprite->sprite3 = mlx_load_png("./graphic/Amaterasu/sprite3");
	cub->sprite->sprite4 = mlx_load_png("./graphic/Amaterasu/sprite4");
}

// put all the pointer inside the struct at NULL
t_cub	*init_struct(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		ft_putstr_fd("Error\nFailed to init struct\n", 2);
		return (NULL);
	}
	cub->has_door = FALSE;
	cub->g_height = GRAPH_HEIGHT;
	cub->g_width = GRAPH_WIDTH;
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	init_sprite(cub);
	cub->minimap = NULL;
	cub->no_xpm = NULL;
	cub->so_xpm = NULL;
	cub->we_xpm = NULL;
	cub->ea_xpm = NULL;
	cub->do_xpm = NULL;
	cub->init_ptr = NULL;
	cub->img_ptr = NULL;
	cub->map = NULL;
	return (cub);
}

static void	free_sprite(t_cub *cub)
{
	if (cub->animate)
		mlx_delete_image(cub->init_ptr, cub->animate);
	if (cub->sprite->sprite1)
		mlx_delete_texture(cub->sprite->sprite1);
	if (cub->sprite->sprite2)
		mlx_delete_texture(cub->sprite->sprite2);
	if (cub->sprite->sprite3)
		mlx_delete_texture(cub->sprite->sprite3);
	if (cub->sprite->sprite4)
		mlx_delete_texture(cub->sprite->sprite4);
	free(cub->sprite);
}

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
	if (cub->minimap)
		mlx_delete_image(cub->init_ptr, cub->minimap);
	free_sprite(cub);
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
