/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:04:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/03 13:19:12 by rbardet-         ###   ########.fr       */
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
	cub->is_animating = 0;
	cub->frame = 0;
	cub->frame_delay = 0;
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

void	animate_sprites(void *param)
{
	t_cub			*cub;
	static double	last_update_time = 0;

	cub = (t_cub *)param;
	cub->frame_delay = 0.001;
	if (!cub || !cub->sprite || !cub->sprite[cub->frame] || !cub->is_animating)
		return ;
	cub->current_time = mlx_get_time();
	if (cub->current_time - last_update_time >= cub->frame_delay)
	{
		if (cub->frame > 0)
			cub->sprite[cub->frame - 1]->enabled = FALSE;
		cub->sprite[cub->frame]->enabled = TRUE;
		mlx_image_to_window(cub->init_ptr, cub->sprite[cub->frame],
			cub->win_width / 2, cub->win_height * 0.40);
		cub->frame++;
		last_update_time = cub->current_time;
	}
	if (!cub->sprite[cub->frame])
	{
		cub->sprite[cub->frame - 1]->enabled = FALSE;
		cub->sprite[0]->enabled = TRUE;
		cub->frame = 0;
		cub->is_animating = 0;
	}
}
