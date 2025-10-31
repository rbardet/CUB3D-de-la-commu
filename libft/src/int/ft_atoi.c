/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 05:11:59 by rbardet-          #+#    #+#             */
/*   Updated: 2025/10/11 20:08:05 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long int	ft_atol(char *nptr)
{
	int			a;
	long int	convert;
	int			min;

	convert = 0;
	a = 0;
	while ((nptr[a] > 8 && nptr[a] < 14) || (nptr[a] == 32))
		a++;
	min = 0;
	if (nptr[a] == '-' || nptr[a] == '+')
	{
		if (nptr[a] == '-')
			min++;
		a++;
	}
	while (nptr[a] >= '0' && nptr[a] <= '9')
	{
		convert *= 10;
		convert += nptr[a] - '0';
		a++;
	}
	if (min % 2 == 1)
		convert *= -1;
	return (convert);
}

int	ft_atoi(char *nptr)
{
	int	a;
	int	convert;
	int	min;

	convert = 0;
	a = 0;
	while ((nptr[a] > 8 && nptr[a] < 14) || (nptr[a] == 32))
		a++;
	min = 0;
	if (nptr[a] == '-' || nptr[a] == '+')
	{
		if (nptr[a] == '-')
			min++;
		a++;
	}
	while (nptr[a] >= '0' && nptr[a] <= '9')
	{
		convert *= 10;
		convert += nptr[a] - '0';
		a++;
	}
	if (min % 2 == 1)
		convert *= -1;
	return (convert);
}

// int main(void)
// {
// 	char str[] = "     23 5aa2358";

// 	printf("%d", ft_atoi(str));
// 	return(0);
// }
