/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 04:53:18 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/21 19:09:44 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
