/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:50:07 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/25 17:14:51 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// debug function to show all the data inside the main struct *cub
void	print_struct(t_cub *cub)
{
	printf("Textures:\n");
	printf("  North: %p\n", cub->no_xpm);
	printf("  South: %p\n", cub->so_xpm);
	printf("  West: %p\n", cub->we_xpm);
	printf("  East: %p\n", cub->ea_xpm);
	printf("  Door: %p\n", cub->do_xpm);
	printf("\nFloor (RGB):\n");
	printf("  Red: %d\n", cub->floor.red);
	printf("  Green: %d\n", cub->floor.green);
	printf("  Blue: %d\n", cub->floor.blue);
	printf("  Value: \033[48;2;%d;%d;%dm       \033[0m\n",
		cub->floor.red, cub->floor.green, cub->floor.blue);
	printf("\nCeiling (RGB):\n");
	printf("  Red: %d\n", cub->ceil.red);
	printf("  Green: %d\n", cub->ceil.green);
	printf("  Blue: %d\n", cub->ceil.blue);
	printf("  Value: \033[48;2;%d;%d;%dm       \033[0m\n",
		cub->ceil.red, cub->ceil.green, cub->ceil.blue);
	printf("\nPlayer:\n");
	printf("  Position: (%d, %d)\n", cub->player.pos_x, cub->player.pos_y);
	printf("  Direction: (%f, %f)\n", cub->player.dir_x, cub->player.dir_y);
	printf("  Plane: (%f, %f)\n", cub->player.plane_x, cub->player.plane_y);
	printf("  Spawn View: %c\n", cub->spawn_view);
	printab(cub->map);
	exit(0);
}

// a boolean function that take the name of the map and move its cursor to
// the 4 last character to see if the map is a .cub file
// return TRUE if it is else return FALSE
t_bool	is_cub(char *argv)
{
	argv += ft_strlen(argv) - 4;
	if (!ft_strcmp(argv, ".cub"))
		return (TRUE);
	else
	{
		ft_putstr_fd("Error\nThe map is not a .cub\n", 2);
		return (FALSE);
	}
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nYou need to pass one map.\n", 2);
		return (127);
	}
	if (!is_cub(argv[1]))
		return (127);
	cub = parse_struct(argv[1]);
	if (!cub)
		exit (127);
	print_struct(cub);
	open_window(cub);
	return (0);
}
