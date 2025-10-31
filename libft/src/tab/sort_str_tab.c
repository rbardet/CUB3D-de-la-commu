/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_str_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:07:49 by throbert          #+#    #+#             */
/*   Updated: 2025/10/11 20:08:05 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	**copy_str_tab(char **tab, int count)
{
	char	**sorted_tab;
	int		i;

	sorted_tab = malloc((count + 1) * sizeof(char *));
	if (!sorted_tab)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sorted_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	sorted_tab[count] = NULL;
	return (sorted_tab);
}

static void	sort_tab(char **tab, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**sort_str_tab(char **tab)
{
	int		count;
	char	**sorted_tab;

	count = 0;
	while (tab[count])
		count++;
	sorted_tab = copy_str_tab(tab, count);
	if (!sorted_tab)
		return (NULL);
	sort_tab(sorted_tab, count);
	return (sorted_tab);
}
