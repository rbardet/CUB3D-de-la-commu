/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:51:13 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 20:24:14 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

#define WIN_HEIGHT 800
#define WIN_WIDTH 1600

#define TILE 20

#define GRAPH_HEIGHT 1000
#define GRAPH_WIDTH 1000

typedef int		t_bool;
#define TRUE 1
#define FALSE 0

#define M_PI 3.14159265358979323846
#define FOV_ANGLE 90

typedef struct s_rgb
{
	int32_t		red;
	int32_t		green;
	int32_t		blue;
}				t_rgb;

typedef struct s_draw
{
	int			tex_num;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			color;
}				t_draw;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	int			map_width;
	int			map_height;
	double		dir_x;
	double		dir_y;
	double		plane_factor;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
}				t_ray;

typedef struct s_img
{
	mlx_texture_t	*texture;
	int				bpp;
	int				line_len;
}				t_img;

typedef struct s_cub
{
	int				win_height;
	int				win_width;
	int				g_height;
	int				g_width;
	mlx_texture_t	*no_xpm;
	mlx_texture_t	*so_xpm;
	mlx_texture_t	*we_xpm;
	mlx_texture_t	*ea_xpm;
	mlx_texture_t	*do_xpm;
	mlx_t			*init_ptr;
	mlx_image_t		*img_ptr;
	char			spawn_view;
	t_rgb			floor;
	t_rgb			ceil;
	t_player		player;
	char			**map;
}				t_cub;

// avoid leak
void			free_struct(void *param);

// parsing
t_cub			*init_struct(void);
char			**copy_and_check_map(t_cub *cub);
int				find_max_len(char **map);
int				skip_space(char *line, int i);
t_rgb			get_rgb(char **rgb_tmp);
void			get_xpm(t_cub *cub);
t_cub			*fill_struct(t_cub *cub);
void			flood_fill(int x, int y, char **map, int *ret);
t_bool			is_one_player(char **map, int i);
t_bool			is_valid_map(t_cub *cub);
t_bool			close_or_not(char **map, int x, int y, t_cub *cub);
t_bool			is_close_map(char **map, int i, t_cub *cub);
int				count_line(char *argv);
char			**loop_copy(int fd, int nb_line);
char			**copy_map(char *argv);
t_bool			is_cub(char *map);
t_cub			*parse_struct(char *map);
t_player		init_player_struct(t_cub *cub, t_player player);

// render
void			draw_wall(t_cub *cub, int x, t_ray ray);
void			open_window(t_cub *cub);
int				minimap(t_cub *cub);
void			render_minimap(t_cub *cub);
t_ray			ray_dist_x(t_cub *cub, t_ray ray);
t_ray			ray_dist_y(t_cub *cub, t_ray ray);
t_ray			init_ray(t_cub *cub, int x);
void			raycast(t_cub *cub);
t_bool			check_collision(t_cub *cub, double x, double y);
t_bool			move_front(t_cub *cub);
t_bool			move_back(t_cub *cub);
t_bool			move_left(t_cub *cub);
t_bool			move_right(t_cub *cub);
t_bool			rotate_right(t_cub *cub);
t_bool			rotate_left(t_cub *cub);
int32_t			get_texture_color(mlx_texture_t *texture,
					int texX, int texY);
void			draw_ceilling(t_cub *cub);
void			draw_floor(t_cub *cub);

// debug

//UTILS

//debug
void			print_xpm_status(void *xpm, char *name);
char			*get_direction_name(char c);
void			print_window_info(t_cub *cub);
void			print_textures_info(t_cub *cub);
void			print_colors_info(t_cub *cub);
void			print_player_info(t_cub *cub);

//debug 2
void			print_player_info(t_cub *cub);
void			print_map_info(t_cub *cub);
void			print_struct(t_cub *cub);
