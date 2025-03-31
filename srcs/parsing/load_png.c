/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:55:45 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 18:01:29 by rbardet-         ###   ########.fr       */
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
static mlx_texture_t *get_png(t_cub *cub, int idx)
{
	int				i;
	mlx_texture_t	*text;
	char			*tmp;

	i = skip_space(cub->map[idx], 3);
	tmp = copy_png(cub->map[idx] + i);
	if (!tmp)
		return (NULL);
	text = mlx_load_png(tmp);
	if (!text)
		return (NULL);
	free(tmp);
	return (text);
}

// load all the png inside the cub struct
void	load_png(t_cub *cub)
{
	cub->no_xpm = get_png(cub, 0);
	if (!cub->no_xpm)
		ft_putstr_fd("Error\nFailed to load North texture\n", 2);
	cub->so_xpm = get_png(cub, 1);
	if (!cub->so_xpm)
		ft_putstr_fd("Error\nFailed to load South texture\n", 2);
	cub->we_xpm = get_png(cub, 2);
	if (!cub->we_xpm)
		ft_putstr_fd("Error\nFailed to load West texture\n", 2);
	cub->ea_xpm = get_png(cub, 3);
	if (!cub->ea_xpm)
		ft_putstr_fd("Error\nFailed to load East texture\n", 2);
	cub->do_xpm = get_png(cub, 4);
	if (!cub->do_xpm)
		ft_putstr_fd("Error\nFailed to load Door texture\n", 2);
}
