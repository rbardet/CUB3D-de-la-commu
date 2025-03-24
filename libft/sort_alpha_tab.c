/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alpha_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:40:38 by throbert          #+#    #+#             */
/*   Updated: 2025/03/11 22:41:02 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	compare_ignore_case(const char *s1, const char *s2)
{
	char	c1;
	char	c2;

	while (*s1 && *s2)
	{
		c1 = ft_toupper((unsigned char)*s1);
		c2 = ft_toupper((unsigned char)*s2);
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
	}
	return (ft_toupper((unsigned char)*s1) - ft_toupper((unsigned char)*s2));
}

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
			if (compare_ignore_case(tab[i], tab[j]) > 0)
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

char	**sort_alpha_tab(char **tab)
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
