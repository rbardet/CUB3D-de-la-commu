/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xmin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:14:57 by rbardet-          #+#    #+#             */
/*   Updated: 2024/11/08 04:28:35 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_min(unsigned int a)
{
	if (a >= 16)
	{
		ft_min(a / 16);
		ft_min(a % 16);
	}
	else
	{
		if (a <= 9)
			ft_putchar (a + '0');
		else
			ft_putchar (a - 10 + 'a');
	}
}

int	ft_printf_xmin(unsigned int a)
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
	ft_min(a);
	return (b);
}
// int main(void)
// {
// 	unsigned int a = 1712312;
// 	ft_printf_xmin(a);
// 	ft_putchar('\n');
// 	printf("%d\n", ft_printf_x(a));
// 	return(0);
// }
