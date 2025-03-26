/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:51:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/26 23:02:15 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void move_forward(t_cub *cub)
{
    if (cub->map[(int)(cub->player.pos_y)][(int)(cub->player.pos_x + cub->player.dir_x * MOVE_SPEED)] == '0')
        cub->player.pos_x += cub->player.dir_x * MOVE_SPEED;
    if (cub->map[(int)(cub->player.pos_y + cub->player.dir_y * MOVE_SPEED)][(int)(cub->player.pos_x)] == '0')
        cub->player.pos_y += cub->player.dir_y * MOVE_SPEED;
    raycast(cub);
}

void move_backward(t_cub *cub)
{
    if (cub->map[(int)(cub->player.pos_y)][(int)(cub->player.pos_x - cub->player.dir_x * MOVE_SPEED)] == '0')
        cub->player.pos_x -= cub->player.dir_x * MOVE_SPEED;
    if (cub->map[(int)(cub->player.pos_y - cub->player.dir_y * MOVE_SPEED)][(int)(cub->player.pos_x)] == '0')
        cub->player.pos_y -= cub->player.dir_y * MOVE_SPEED;
    raycast(cub);
}

void move_left(t_cub *cub)
{
    double perp_x = -cub->player.dir_y;
    double perp_y = cub->player.dir_x;

    if (cub->map[(int)(cub->player.pos_y)][(int)(cub->player.pos_x + perp_x * MOVE_SPEED)] == '0')
        cub->player.pos_x += perp_x * MOVE_SPEED;
    if (cub->map[(int)(cub->player.pos_y + perp_y * MOVE_SPEED)][(int)(cub->player.pos_x)] == '0')
        cub->player.pos_y += perp_y * MOVE_SPEED;
    raycast(cub);
}

void move_right(t_cub *cub)
{
    double perp_x = cub->player.dir_y;
    double perp_y = -cub->player.dir_x;

    if (cub->map[(int)(cub->player.pos_y)][(int)(cub->player.pos_x + perp_x * MOVE_SPEED)] == '0')
        cub->player.pos_x += perp_x * MOVE_SPEED;
    if (cub->map[(int)(cub->player.pos_y + perp_y * MOVE_SPEED)][(int)(cub->player.pos_x)] == '0')
        cub->player.pos_y += perp_y * MOVE_SPEED;
    raycast(cub);
}

void rotate_right(t_cub *cub)
{
    double oldDirX = cub->player.dir_x;
    cub->player.dir_x = cub->player.dir_x * cos(-ROT_SPEED) - cub->player.dir_y * sin(-ROT_SPEED);
    cub->player.dir_y = oldDirX * sin(-ROT_SPEED) + cub->player.dir_y * cos(-ROT_SPEED);
    double oldPlaneX = cub->player.plane_x;
    cub->player.plane_x = cub->player.plane_x * cos(-ROT_SPEED) - cub->player.plane_y * sin(-ROT_SPEED);
    cub->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + cub->player.plane_y * cos(-ROT_SPEED);
    raycast(cub);
}

void rotate_left(t_cub *cub)
{
    double oldDirX = cub->player.dir_x;
    cub->player.dir_x = cub->player.dir_x * cos(ROT_SPEED) - cub->player.dir_y * sin(ROT_SPEED);
    cub->player.dir_y = oldDirX * sin(ROT_SPEED) + cub->player.dir_y * cos(ROT_SPEED);
    double oldPlaneX = cub->player.plane_x;
    cub->player.plane_x = cub->player.plane_x * cos(ROT_SPEED) - cub->player.plane_y * sin(ROT_SPEED);
    cub->player.plane_y = oldPlaneX * sin(ROT_SPEED) + cub->player.plane_y * cos(ROT_SPEED);
    raycast(cub);
}
