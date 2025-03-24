/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 06:57:15 by rbardet-          #+#    #+#             */
/*   Updated: 2024/11/08 04:38:41 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	ft_printf_c(char c)
{
	int	a;

	a = 0;
	write(1, &c, 1);
	a++;
	return (a);
}

// int main(void)
// {
// 	char c = 'r';
// 	ft_printf_c(c);
// 	return(0);
// }
