/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:51:13 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/26 17:58:09 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define WIN_HEIGHT 1200
#define WIN_WIDTH 900

#define Tile (WIN_HEIGHT / 120) % WIN_WIDTH

#define GRAPH_HEIGHT 64
#define GRAPH_WIDTH 64

typedef int		t_bool;
#define TRUE 1
#define FALSE 0

#define M_PI 3.14159265358979323846
#define FOV_ANGLE 66
#define PLANE_FACTOR tan((FOV_ANGLE * M_PI / 180) / 2)

typedef struct s_rgb
{
	int			red;
	int			green;
	int			blue;
}				t_rgb;

typedef struct s_player
{
	int			pos_x;
	int			pos_y;
	int			map_width;
	int			map_height;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
}				t_player;

typedef struct s_cub
{
	int			win_height;
	int			win_width;
	void		*no_xpm;
	void		*so_xpm;
	void		*we_xpm;
	void		*ea_xpm;
	void		*do_xpm;
	void		*init_ptr;
	void		*win_ptr;
	char		spawn_view;
	void		*img_ptr;
	t_rgb		floor;
	t_rgb		ceil;
	t_player	player;
	char		**map;
}				t_cub;

// avoid leak
int				free_struct(t_cub *cub);

// parsing
int				find_max_len(char **map);
int				skip_space(char *line, int i);
t_rgb			get_rgb(char **rgb_tmp);
void			get_xpm(t_cub *cub);
t_cub			*fill_struct(t_cub *cub);
void			flood_fill(int x, int y, char **map, int *ret);
t_bool			is_one_player(char **map, int i);
t_bool			is_valid_map(t_cub *cub);
t_bool			close_or_not(char **map, int x, int y);
t_bool			is_close_map(char **map, int i, t_cub *cub);
int				count_line(char *argv);
char			**loop_copy(int fd, int nb_line);
char			**copy_map(char *argv);
t_bool			is_cub(char *map);
t_cub			*parse_struct(char *map);
t_player		init_player_struct(t_cub *cub);

// render
void			open_window(t_cub *cub);
int				handle_keypress(int key, t_cub *cub);
int				minimap(t_cub *cub);
void			render_minimap(t_cub *cub);

// debug

void			print_struct(t_cub *cub);
