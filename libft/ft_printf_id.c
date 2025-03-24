/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:34:19 by rbardet-          #+#    #+#             */
/*   Updated: 2024/11/08 04:42:41 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static int	ft_nbrr(int n)
{
	int	a;

	a = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		a++;
	while (n != 0)
	{
		n /= 10;
		a++;
	}
	return (a);
}

static char	*ft_itoaa(int n)
{
	int			longueur;
	char		*str;
	int			sign;

	sign = 1;
	longueur = ft_nbrr(n);
	str = malloc(sizeof(char) * (longueur + 1));
	if (!str)
		return (free(str), NULL);
	str[longueur] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		sign *= -1;
	}
	while (n != 0)
	{
		longueur--;
		str[longueur] = ((n % 10) * sign) + '0';
		n /= 10;
	}
	return (str);
}

int	ft_printf_id(int c)
{
	int		a;
	int		b;
	char	*str1;

	a = ft_nbrr(c);
	str1 = ft_itoaa(c);
	b = 0;
	while (str1[b] != '\0')
	{
		write(1, &str1[b], 1);
		b++;
	}
	free(str1);
	return (a);
}

// static void	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }
// int main(void)
// {
// 	int a = -2147483648;
// 	int b = 9;
// 	ft_printf_id(a);
// 	ft_putchar('\n');
// 	printf("%d\n", ft_nbr(a));
// 	ft_printf_id(b);
// 	ft_putchar('\n');
// 	printf("%d", ft_nbr(b));
// 	return(0);
// }
