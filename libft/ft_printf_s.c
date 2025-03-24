/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:09:24 by rbardet-          #+#    #+#             */
/*   Updated: 2024/11/08 04:40:54 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	ft_printf_s(char *str)
{
	int	a;
	int	b;

	if (!str)
		return (write(1, "(null)", 6));
	a = 0;
	b = ft_strlen(str);
	while (str[a] != '\0')
	{
		write(1, &str[a], 1);
		a++;
	}
	return (b);
}
// int main(void)
// {
// 	char str[] = "Lille OSC";
// 	char c[] = "A";
// 	ft_printf_s(str);
// 	write(1, "\n", 1);
// 	printf("%d\n", ft_strlen(str));
// 	return(0);
// }
