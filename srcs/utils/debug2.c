/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:55:50 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/27 14:29:38 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_player_info(t_cub *cub)
{
	printf("\n\033[1;34m[Player Info]\033[0m\n");
	printf("Position: X=%f Y=%f\n", cub->player.pos_x, cub->player.pos_y);
	printf("Direction: X=%.2f Y=%.2f\n", cub->player.dir_x, cub->player.dir_y);
	printf("Plane: X=%.2f Y=%.2f\n", cub->player.plane_x, cub->player.plane_y);
	printf("Spawn View: %s (%c)\n", get_direction_name(cub->spawn_view),
		cub->spawn_view);
	printf("Map Dimensions: Width=%d Height=%d\n", cub->player.map_width,
		cub->player.map_height);
}

void	print_map_info(t_cub *cub)
{
	printf("\n\033[1;34m[Map Content]\033[0m\n");
	printf("Map width: %d\n", cub->player.map_width);
	printf("Map height: %d\n", cub->player.map_height);
	if (!cub->map)
		printf("❌  No map loaded!\n");
}

/**
 * @brief Prints debug information about the current game state.
 * @param cub A pointer to the main game structure.
 */
void	print_struct(t_cub *cub)
{
	printf("\n\033[1;36m======= [CUB3D DEBUG INFO] =======\033[0m\n");
	print_window_info(cub);
	print_textures_info(cub);
	print_colors_info(cub);
	print_player_info(cub);
	print_map_info(cub);
	printf("\033[1;36m==================================\033[0m\n\n");
}
