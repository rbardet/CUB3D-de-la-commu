/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:49:06 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/22 13:00:20 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char unsigned	*str;
	size_t			a;

	str = (char unsigned *) s;
	a = 0;
	while (n != 0)
	{
		str[a] = c;
		str++;
		n--;
	}
	return (s);
}
// int main(void)
// {
// 	char str[] = "LILLE OSC";
// 	printf("%s", (char *)ft_memset(str, 'y', 4));
// 	return(0);
// }
