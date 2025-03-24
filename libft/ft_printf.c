/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 06:18:45 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/21 19:09:44 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

static int	ft_format(va_list print, char str)
{
	int	a;

	a = 0;
	if (str == 'c')
		a += ft_printf_c(va_arg(print, int));
	else if (str == 's')
		a += ft_printf_s(va_arg(print, char *));
	else if (str == 'p')
		a += ft_printf_p(va_arg(print, unsigned long long));
	else if ((str == 'd') || (str == 'i'))
		a += ft_printf_id(va_arg(print, int));
	else if (str == 'u')
		a += ft_printf_u(va_arg(print, unsigned int));
	else if (str == 'x')
		a += ft_printf_xmin(va_arg(print, unsigned int));
	else if (str == 'X')
		a += ft_printf_xmaj(va_arg(print, unsigned int));
	else if (str == '%')
		a += ft_printf_prc();
	return (a);
}

int	ft_printf(char *str, ...)
{
	int		a;
	int		b;
	va_list	print;

	if (!str)
		return (-1);
	a = 0;
	b = 0;
	va_start (print, str);
	while (str[a] != '\0')
	{
		if (str[a] == '%')
		{
			b += ft_format(print, str[a + 1]);
			a += 2;
		}
		else
		{
			write(1, &str[a], 1);
			a++;
			b++;
		}
	}
	va_end(print);
	return (b);
}

// int	main(void)
// {
// 	char c = 'R';
// 	ft_printf("%c\n", c);
// 	printf("%c\n", c);

// 	char str[] = "Lille OSC";
// 	ft_printf("%s\n", str);
// 	printf("%s\n", str);

// 	char *str1 = "82157";
// 	ft_printf("%p\n", str1);
// 	printf("%p\n", str1);

// 	int nbr = -2147483648;
// 	ft_printf("%d\n", nbr);
// 	printf("%d\n", nbr);

// 	int chf = 9;
// 	ft_printf("%i\n", chf);
// 	printf("%i\n", chf);

// 	unsigned int b = -18;
// 	ft_printf("%u\n", b);
// 	printf("%u\n", b);

// 	unsigned int x = 1712312;
// 	ft_printf("%x\n", x);
// 	printf("%x\n", x);

// 	ft_printf("%X\n", x);
// 	printf("%X\n", x);

// 	ft_printf("%%\n");
// 	printf("%%\n");
// 	return (0);
// }
