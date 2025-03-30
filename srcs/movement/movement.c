/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:51:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/30 19:27:46 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Check if the player is colliding with a wall or a door.
 * @param cub The main struct of the program.
 * @param x The x coordinate of the player.
 * @param y The y coordinate of the player.
 * @return FALSE if there is a collision, TRUE if not.
 */
t_bool	check_collision(t_cub *cub, double x, double y)
{
	if (cub->map[(int)y][(int)x] == '1' || cub->map[(int)y][(int)x] == 'D')
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Move player forward if possible.
 * @param cub The main struct of the program.
 * @return TRUE if the player was able to move, FALSE if there was a collision.
 */
t_bool	move_front(t_cub *cub)
{
	double	tmp_x;
	double	tmp_y;
	t_bool	move;

	move = FALSE;
	tmp_x = cub->player.pos_x;
	tmp_y = cub->player.pos_y;
	cub->player.pos_x += cub->player.dir_x * MOVE_SPEED;
	if (!check_collision(cub, cub->player.pos_x, cub->player.pos_y))
		cub->player.pos_x = tmp_x;
	else
		move = TRUE;
	cub->player.pos_y += cub->player.dir_y * MOVE_SPEED;
	if (!check_collision(cub, cub->player.pos_x, cub->player.pos_y))
		cub->player.pos_y = tmp_y;
	else
		move = TRUE;
	return (move);
}

/**
 * @brief Move player backward if possible.
 * @param cub The main struct of the program.
 * @return TRUE if the player was able to move, FALSE if there was a collision.
 */
t_bool	move_back(t_cub *cub)
{
	double	tmp_x;
	double	tmp_y;
	t_bool	move;

	move = FALSE;
	tmp_x = cub->player.pos_x;
	tmp_y = cub->player.pos_y;
	cub->player.pos_x -= cub->player.dir_x * MOVE_SPEED;
	if (check_collision(cub, cub->player.pos_x, cub->player.pos_y))
		move = TRUE;
	else
		cub->player.pos_x = tmp_x;
	cub->player.pos_y -= cub->player.dir_y * MOVE_SPEED;
	if (check_collision(cub, cub->player.pos_x, cub->player.pos_y))
		move = TRUE;
	else
		cub->player.pos_y = tmp_y;
	return (move);
}

/**
 * @brief Move player to the left if possible.
 * @param cub The main struct of the program.
 * @return TRUE if the player was able to move,
 * FALSE if there was a collision.
 */
t_bool	move_left(t_cub *cub)
{
	double	tmp_x;
	double	tmp_y;
	t_bool	move;

	move = FALSE;
	tmp_x = cub->player.pos_x;
	tmp_y = cub->player.pos_y;
	cub->player.pos_x -= cub->player.plane_x * MOVE_SPEED;
	if (!check_collision(cub, cub->player.pos_x, cub->player.pos_y))
		cub->player.pos_x = tmp_x;
	else
		move = TRUE;
	cub->player.pos_y -= cub->player.plane_y * MOVE_SPEED;
	if (!check_collision(cub, cub->player.pos_x, cub->player.pos_y))
		cub->player.pos_y = tmp_y;
	else
		move = TRUE;
	return (move);
}

/**
 * @brief Move player to the right if possible.
 * @param cub The main struct of the program.
 * @return TRUE if the player was able to move, FALSE if there was a collision.
 */
t_bool	move_right(t_cub *cub)
{
	double	tmp_x;
	double	tmp_y;
	t_bool	move;

	move = FALSE;
	tmp_x = cub->player.pos_x;
	tmp_y = cub->player.pos_y;
	cub->player.pos_x += cub->player.plane_x * MOVE_SPEED;
	if (!check_collision(cub, cub->player.pos_x, cub->player.pos_y))
		cub->player.pos_x = tmp_x;
	else
		move = TRUE;
	cub->player.pos_y += cub->player.plane_y * MOVE_SPEED;
	if (!check_collision(cub, cub->player.pos_x, cub->player.pos_y))
		cub->player.pos_y = tmp_y;
	else
		move = TRUE;
	return (move);
}
