/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:55:45 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/01 11:52:17 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// copy the line to the \n and return it , its a char * to the png
char	*copy_png(char *line)
{
	char	*text;
	int		i;

	text = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!text)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		text[i] = line[i];
		i++;
	}
	text[i] = '\0';
	return (text);
}

// extract the png from the map and return it
static mlx_texture_t	*get_png(char **arg, int idx)
{
	int				i;
	mlx_texture_t	*text;
	char			*tmp;

	i = skip_space(arg[idx], 3);
	tmp = copy_png(arg[idx] + i);
	if (!tmp)
		return (NULL);
	text = mlx_load_png(tmp);
	if (!text)
		return (NULL);
	free(tmp);
	return (text);
}

// load all the png inside the cub struct
void	load_png(t_cub *cub, char **tmp)
{
	int	has_door;

	has_door = 0;
	if (cub->has_door == TRUE)
	{
		cub->do_xpm = get_png(tmp, 1);
		if (!cub->do_xpm)
			ft_putstr_fd("Error\nFailed to load Door texture\n", 2);
		has_door += 1;
	}
	cub->no_xpm = get_png(tmp, 3 + has_door);
	if (!cub->no_xpm)
		ft_putstr_fd("Error\nFailed to load North texture\n", 2);
	cub->so_xpm = get_png(tmp, 4 + has_door);
	if (!cub->so_xpm)
		ft_putstr_fd("Error\nFailed to load South texture\n", 2);
	cub->we_xpm = get_png(tmp, 5 + has_door);
	if (!cub->we_xpm)
		ft_putstr_fd("Error\nFailed to load West texture\n", 2);
	cub->ea_xpm = get_png(tmp, 1 + has_door);
	if (!cub->ea_xpm)
		ft_putstr_fd("Error\nFailed to load East texture\n", 2);
}
