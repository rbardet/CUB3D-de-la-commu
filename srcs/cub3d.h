/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:51:13 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/24 20:32:53 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define WIN_HEIGHT 1200
#define WIN_WIDTH 900

#define GRAPH_HEIGHT 64
#define GRAPH_WIDTH 64

typedef int	t_bool;
#define TRUE 1
#define FALSE 0

typedef struct s_rgb
{
	int		red;
	int		green;
	int		blue;
}			t_rgb;

typedef struct s_cub
{
	int		win_height;
	int		win_width;
	void	*no_xpm;
	void	*so_xpm;
	void	*we_xpm;
	void	*ea_xpm;
	void	*do_xpm;
	void	*init_ptr;
	void	*win_ptr;
	t_rgb	floor;
	t_rgb	ceil;
	int		x;
	int		y;
	char	**map;
}			t_cub;

// avoid leak
int			free_struct(t_cub *cub);

// parsing
int			skip_space(char *line, int i);
t_rgb		get_rgb(char **rgb_tmp);
void		get_xpm(t_cub *cub);
t_cub		*fill_struct(t_cub *cub);
void		flood_fill(int x, int y, char **map, int *ret);
t_bool		is_one_player(char **map, int i);
t_bool		is_valid_map(t_cub *cub);
t_bool		close_or_not(char **map, int x, int y);
t_bool		is_close_map(char **map, int i, t_cub *cub);
int			count_line(char *argv);
char		**loop_copy(int fd, int nb_line);
char		**copy_map(char *argv);
t_bool		is_cub(char *map);
t_cub		*parse_struct(char *map);

// render
void		open_window(t_cub *cub);
int			handle_keypress(int key, t_cub *cub);

int			skip_space(char *line, int i);
t_rgb		get_rgb(char **rgb_tmp);
void		get_xpm(t_cub *cub);
t_cub		*fill_struct(t_cub *cub);
void		flood_fill(int x, int y, char **map, int *ret);
t_bool		is_one_player(char **map, int i);
t_bool		is_valid_map(t_cub *cub);
t_bool		close_or_not(char **map, int x, int y);
t_bool		is_close_map(char **map, int i, t_cub *cub);
int			count_line(char *argv);
char		**loop_copy(int fd, int nb_line);
char		**copy_map(char *argv);
t_bool		is_cub(char *map);
t_cub		*parse_struct(char *map);

// render

void		open_window(t_cub *cub);
int			handle_keypress(int key, t_cub *cub);

// debug

void		print_struct(t_cub *cub);
