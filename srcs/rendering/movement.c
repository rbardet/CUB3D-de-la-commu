/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:51:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 20:15:18 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_bool	check_collision(t_cub *cub, double x, double y)
{
	if (cub->map[(int)y][(int)x] == '1')
		return (FALSE);
	return (TRUE);
}

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
