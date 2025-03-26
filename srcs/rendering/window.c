/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:48:34 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/26 22:44:11 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

// function used to free the main struct of the project
int	free_struct(t_cub *cub)
{
	if (cub->init_ptr && cub->win_ptr)
		mlx_destroy_window(cub->init_ptr, cub->win_ptr);
	if (cub->init_ptr)
		mlx_destroy_display(cub->init_ptr);
	if (cub->init_ptr)
		free(cub->init_ptr);
	if (cub->map)
		free_tab(cub->map);
	if (cub)
		free(cub);
	exit (0);
}

void move_forward(t_cub *cub)
{
	if (cub->map[(int)(cub->player.pos_y)][(int)(cub->player.pos_x + cub->player.dir_x * MOVE_SPEED)] == '0')
		cub->player.pos_x += cub->player.dir_x * MOVE_SPEED;
	if (cub->map[(int)(cub->player.pos_y + cub->player.dir_y * MOVE_SPEED)][(int)(cub->player.pos_x)] == '0')
		cub->player.pos_y += cub->player.dir_y * MOVE_SPEED;
}

void move_backward(t_cub *cub)
{
	if (cub->map[(int)(cub->player.pos_y)][(int)(cub->player.pos_x - cub->player.dir_x * MOVE_SPEED)] == '0')
		cub->player.pos_x -= cub->player.dir_x * MOVE_SPEED;
	if (cub->map[(int)(cub->player.pos_y - cub->player.dir_y * MOVE_SPEED)][(int)(cub->player.pos_x)] == '0')
		cub->player.pos_y -= cub->player.dir_y * MOVE_SPEED;
}

void rotate_right(t_cub *cub)
{
	double oldDirX = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(-ROT_SPEED) - cub->player.dir_y * sin(-ROT_SPEED);
	cub->player.dir_y = oldDirX * sin(-ROT_SPEED) + cub->player.dir_y * cos(-ROT_SPEED);
	double oldPlaneX = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(-ROT_SPEED) - cub->player.plane_y * sin(-ROT_SPEED);
	cub->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + cub->player.plane_y * cos(-ROT_SPEED);
}

void rotate_left(t_cub *cub)
{
	double oldDirX = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(ROT_SPEED) - cub->player.dir_y * sin(ROT_SPEED);
	cub->player.dir_y = oldDirX * sin(ROT_SPEED) + cub->player.dir_y * cos(ROT_SPEED);
	double oldPlaneX = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(ROT_SPEED) - cub->player.plane_y * sin(ROT_SPEED);
	cub->player.plane_y = oldPlaneX * sin(ROT_SPEED) + cub->player.plane_y * cos(ROT_SPEED);
}

// check the keypressed to see wich action need to be done
int handle_keypress(int keycode, t_cub *cub)
{
	if (keycode == XK_Up)
		move_forward(cub);
	else if (keycode == XK_Down)
		move_backward(cub);
	else if (keycode == XK_Left)
		rotate_left(cub);
	else if (keycode == XK_Right)
		rotate_right(cub);
	raycast(cub);
	return (0);
}

// open the a window with the size defined in the Header
void	open_window(t_cub *cub)
{
	cub->win_ptr = mlx_new_window(cub->init_ptr, cub->win_width,
			cub->win_height, "cub3d");
	if (!cub->win_ptr)
	{
		ft_putstr_fd("Error\nCouldn't create the windowd\n", 2);
		mlx_destroy_window(cub->init_ptr, cub->win_ptr);
		mlx_destroy_display(cub->init_ptr);
		free(cub->init_ptr);
		return ;
	}
	raycast(cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, &handle_keypress, cub);
	mlx_hook(cub->win_ptr, 17, 0, (int (*)())free_struct, cub);
	mlx_hook(cub->win_ptr, 12, 0, (int (*)())render_minimap, cub);
	mlx_loop(cub->init_ptr);
	return ;
}
