/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:04:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/01 07:08:11 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static mlx_texture_t	**init_sprite_png(void)
{
	mlx_texture_t	**text;
	char			*tmp;
	char			*tmp2;
	char			*tmp3;
	int				i;

	text = malloc(sizeof(mlx_texture_t *) * (SPRITE + 1));
	if (!text)
		return (NULL);
	i = 0;
	while (i < SPRITE)
	{
		tmp = "./graphic/anim/frame-";
		tmp2 = ft_itoa(i + 1);
		tmp3 = ft_strjoin(tmp, tmp2);
		free(tmp2);
		tmp2 = ft_strjoin(tmp3, ".png");
		free(tmp3);
		text[i] = mlx_load_png(tmp2);
		free(tmp2);
		i++;
	}
	text[i] = NULL;
	return (text);
}

t_cub	*init_sprite(t_cub *cub)
{
	mlx_texture_t	**text;
	int				i;

	i = 0;
	text = init_sprite_png();
	cub->sprite = malloc(sizeof(mlx_image_t *) * (SPRITE + 1));
	if (!cub->sprite)
		return (free_struct(cub), NULL);
	while (text[i] && i < SPRITE)
	{
		cub->sprite[i] = mlx_texture_to_image(cub->init_ptr, text[i]);
		mlx_delete_texture(text[i]);
		i++;
	}
	cub->sprite[i] = NULL;
	free(text);
	return (cub);
}

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
