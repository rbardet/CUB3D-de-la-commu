/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:21:44 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/01 05:50:49 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_cub	*init_sprite(t_cub *cub)
{
	mlx_texture_t	**text;

	text = malloc(sizeof(mlx_texture_t *) * (4));
	if (!text)
		return (NULL);
	text[0] = mlx_load_png("./graphic/sprite1.png");
	text[1] = mlx_load_png("./graphic/sprite2.png");
	text[2] = mlx_load_png("./graphic/sprite3.png");
	text[3] = mlx_load_png("./graphic/sprite4.png");
	cub->sprite = malloc(sizeof(mlx_image_t *) * (5));
	if (!cub->sprite)
		return (NULL);
	cub->sprite[0] = mlx_texture_to_image(cub->init_ptr, text[0]);
	cub->sprite[1] = mlx_texture_to_image(cub->init_ptr, text[1]);
	cub->sprite[2] = mlx_texture_to_image(cub->init_ptr, text[2]);
	cub->sprite[3] = mlx_texture_to_image(cub->init_ptr, text[3]);
	cub->sprite[4] = NULL;
	mlx_delete_texture(text[0]);
	mlx_delete_texture(text[1]);
	mlx_delete_texture(text[2]);
	mlx_delete_texture(text[3]);
	free(text);
	if (!cub->sprite || !cub->sprite[0] || !cub->sprite[1]
		|| !cub->sprite[2] || !cub->sprite[3])
		return (free_struct(cub), NULL);
	return (cub);
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
	cub->minimap = NULL;
	cub->init_ptr = NULL;
	cub->img_ptr = NULL;
	cub->map = NULL;
	cub->no_xpm = NULL;
	cub->so_xpm = NULL;
	cub->we_xpm = NULL;
	cub->ea_xpm = NULL;
	cub->do_xpm = NULL;
	return (cub);
}

static void	free_sprite(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->sprite[i])
	{
		mlx_delete_image(cub->init_ptr, cub->sprite[i]);
		i++;
	}
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
