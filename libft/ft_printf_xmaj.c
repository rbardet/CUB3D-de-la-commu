/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xmaj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:35:54 by rbardet-          #+#    #+#             */
/*   Updated: 2024/11/08 04:28:32 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_maj(unsigned int a)
{
	if (a >= 16)
	{
		ft_maj(a / 16);
		ft_maj(a % 16);
	}
	else
	{
		if (a <= 9)
			ft_putchar(a + '0');
		else
			ft_putchar(a - 10 + 'A');
	}
}

int	ft_printf_xmaj(unsigned int a)
{
	int				b;
	unsigned int	c;

	b = 0;
	c = a;
	if (a == 0)
		b = 1;
	else
	{
		while (c != 0)
		{
			c /= 16;
			b++;
		}
	}
	ft_maj(a);
	return (b);
}
// int main(void)
// {
// 	unsigned long a = 1515151515151515;
// 	ft_printf_xmaj(a);
// 	ft_putchar('\n');
// 	printf("%d\n", ft_printf_xmaj(a));
// 	return(0);
// }
