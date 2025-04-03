/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:51:57 by rbardet-          #+#    #+#             */
/*   Updated: 2025/04/03 12:52:36 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// convert the rgb code in the char ** in a new t_rgb
// if the rgb is not in range of 0 to 255 or contain a letter
// set the value to -1 otherwise give it the code
t_rgb	get_rgb(char **rgb_tmp)
{
	t_rgb	rgb;
	int		i;
	int32_t	tmp;
	char	*trim;

	i = skip_space(rgb_tmp[0], 2);
	tmp = (int32_t)ft_atoi(rgb_tmp[0] + i);
	trim = ft_strtrim(rgb_tmp[2], "\n");
	if (tmp < 0 || tmp > 255 || !ft_isdigital(rgb_tmp[0] + i))
		rgb.red = -1;
	else
		rgb.red = tmp;
	tmp = (int32_t)ft_atoi(rgb_tmp[1]);
	if (tmp < 0 || tmp > 255 || !ft_isdigital(rgb_tmp[1]))
		rgb.green = -1;
	else
		rgb.green = tmp;
	tmp = (int32_t)ft_atoi(rgb_tmp[2]);
	if (tmp < 0 || tmp > 255 || !ft_isdigital(trim))
		rgb.blue = -1;
	else
		rgb.blue = tmp;
	free(trim);
	return (rgb);
}
