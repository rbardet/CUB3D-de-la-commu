/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:07:23 by throbert          #+#    #+#             */
/*   Updated: 2025/03/25 17:10:42 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	printab(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab && tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '1')
				printf("\x1B[41m");
			else if (tab[i][j] == '0')
				printf("\x1B[44m");
			else if (tab[i][j] == 'D')
				printf("\x1B[43m");
			else
				printf("\x1B[0m");
			printf("  ");
			printf("\x1B[0m");
			j++;
		}
		printf("\n");
		i++;
	}
}

