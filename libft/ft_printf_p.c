/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 06:34:18 by rbardet-          #+#    #+#             */
/*   Updated: 2024/11/08 04:28:20 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_convert(unsigned long long a)
{
	if (a >= 16)
	{
		ft_convert(a / 16);
		ft_convert(a % 16);
	}
	else
	{
		if (a <= 9)
			ft_putchar(a + '0');
		else
			ft_putchar(a - 10 + 'a');
	}
}

int	ft_printf_p(unsigned long long a)
{
	int	b;

	if (!a)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	b = 2;
	if (a == 0)
	{
		ft_putchar('0');
		b++;
		return (b);
	}
	else
	{
		ft_convert(a);
		while (a != 0)
		{
			a /= 16;
			b++;
		}
	}
	return (b);
}
// int main(void)
// {
// 	unsigned long long a = 123150;
// 	ft_printf_p(a);
// 	write(1, "\n", 1);
// 	printf("%d", ft_printf_p(a));
// 	return 0;
// }
