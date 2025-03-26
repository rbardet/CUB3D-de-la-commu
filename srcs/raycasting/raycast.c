#include "../cub3d.h"

void	draw_vertical_line(t_cub *cub, int x, int start, int end, int color)
{
	for (int y = start; y <= end; y++)
		mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y, color);
}

void	draw_floor_and_ceiling(t_cub *cub)
{
	for (int y = 0; y < WIN_HEIGHT / 2; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y,
				(cub->ceil.red << 16) | (cub->ceil.green << 8) | cub->ceil.blue);
	for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			mlx_pixel_put(cub->init_ptr, cub->win_ptr, x, y,
				(cub->floor.red << 16) | (cub->floor.green << 8) | cub->floor.blue);
}

void	perform_dda(t_cub *cub, int *map_x, int *map_y, double *side_dist_x,
		double *side_dist_y, double delta_dist_x, double delta_dist_y,
		int step_x, int step_y, int *side)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (*side_dist_x < *side_dist_y)
		{
			*side_dist_x += delta_dist_x;
			*map_x += step_x;
			*side = 0;
		}
		else
		{
			*side_dist_y += delta_dist_y;
			*map_y += step_y;
			*side = 1;
		}
		if (cub->map[*map_y][*map_x] == '1')
			hit = 1;
	}
}

void	raycast(t_cub *cub)
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

	draw_floor_and_ceiling(cub);
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		camera_x = 2 * x / (double)WIN_WIDTH - 1;
		ray_dir_x = cub->player.dir_x + cub->player.plane_x * camera_x;
		ray_dir_y = cub->player.dir_y + cub->player.plane_y * camera_x;
		map_x = 11;
		map_y = 10;
		delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (cub->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - cub->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (cub->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - cub->player.pos_y) * delta_dist_y;
		}
		perform_dda(cub, &map_x, &map_y, &side_dist_x, &side_dist_y,
			delta_dist_x, delta_dist_y, step_x, step_y, &side);
		perp_wall_dist = (side == 0) ? (map_x - cub->player.pos_x + (1 - step_x)
				/ 2) / ray_dir_x : (map_y - cub->player.pos_y + (1 - step_y)
				/ 2) / ray_dir_y;
		line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;
		draw_vertical_line(cub, x, draw_start, draw_end, color);
	}
}
