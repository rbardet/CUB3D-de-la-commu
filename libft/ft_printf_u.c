/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:37:42 by rbardet-          #+#    #+#             */
/*   Updated: 2024/11/08 04:28:30 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_printf_u(unsigned int a)
{
	int	b;

	b = 0;
	if (a == 0)
	{
		ft_putchar('0');
		b++;
		return (b);
	}
	if (a >= 10)
	{
		b += ft_printf_u(a / 10);
		a = a % 10;
	}
	ft_putchar(a + '0');
	b++;
	return (b);
}
// int main(void)
// {
// 	unsigned int a = -90;
// 	int b = ft_printf_u(a);
// 	ft_putchar('\n');
// 	printf("%d", b);
// 	return(0);
// }
