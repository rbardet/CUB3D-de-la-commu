/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:10:48 by rbardet-          #+#    #+#             */
/*   Updated: 2025/10/11 20:08:05 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_tabtabchr(char **tab, char *c)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] != '\0')
		{
			while (tab[i][j] == c[j] && tab[i][j] && c[j])
				j++;
			if (c[j] == '\0')
				return (&tab[i]);
			break ;
		}
		i++;
	}
	if (c[j] == '\0')
		return (&tab[i]);
	return (NULL);
}

char	**ft_tabchr(char **tab, int c)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] != '\0')
		{
			if (tab[i][j] == c)
				return (&tab[i]);
			j++;
		}
		i++;
	}
	if (c == '\0')
		return (&tab[i]);
	return (NULL);
}
