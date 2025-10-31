/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 04:53:18 by rbardet-          #+#    #+#             */
/*   Updated: 2025/10/11 20:08:05 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char unsigned	*str;

	str = (char unsigned *)s;
	while (n != 0)
	{
		if (*str == (char unsigned)c)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
// int main(void)
// {
// 	char str[] = "LILLE OSC";
// 	printf("%p", ft_memchr(str, ' ', 100));
// 	return(0);
// }
