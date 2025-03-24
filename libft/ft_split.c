/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:46:00 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/23 16:33:24 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	est_dans_charset2(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*copier_mot(char *str, int debut, int fin)
{
	char	*mot;
	int		i;

	mot = malloc((fin - debut + 1) * sizeof(char));
	if (!mot)
		return (NULL);
	i = 0;
	while (debut < fin)
	{
		mot[i] = str[debut];
		i++;
		debut++;
	}
	mot[i] = '\0';
	return (mot);
}

static void	*free_tableau(char **tab, int k)
{
	while (k > 0)
	{
		k--;
		free(tab[k]);
	}
	free(tab);
	return (NULL);
}

static char	**allouer_add_tab(char *str, char *c, int nb_mot, char **tab)
{
	int	i;
	int	k;
	int	debut;

	i = 0;
	k = 0;
	while (str[i] && k < nb_mot)
	{
		while (str[i] && est_dans_charset2(str[i], c))
			i++;
		debut = i;
		while (str[i] && !est_dans_charset2(str[i], c))
			i++;
		if (i > debut)
		{
			tab[k] = copier_mot(str, debut, i);
			if (!tab[k])
				return (free_tableau(tab, k));
			k++;
		}
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split(char *str, char charset)
{
	int		nb_mots;
	char	tmp[2];
	char	**tableau;
	int		i;

	tmp[0] = charset;
	tmp[1] = '\0';
	i = 0;
	nb_mots = 0;
	while (str[i])
	{
		if (!est_dans_charset2(str[i], tmp))
		{
			if (i == 0 || est_dans_charset2(str[i - 1], tmp))
				nb_mots++;
		}
		i++;
	}
	tableau = malloc((nb_mots + 1) * sizeof(char *));
	if (!tableau)
		return (NULL);
	return (allouer_add_tab(str, tmp, nb_mots, tableau));
}
