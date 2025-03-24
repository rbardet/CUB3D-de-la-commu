/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:38:58 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/24 13:13:41 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char unsigned	*src1;
	char unsigned	*dest1;
	size_t			a;

	if ((src == NULL) && (dest == NULL))
		return (NULL);
	src1 = (char unsigned *) src;
	dest1 = (char unsigned *) dest;
	a = 0;
	if (dest1 < src1)
	{
		while (n != 0)
		{
			dest1[a] = src1[a];
			n--;
			a++;
		}
	}
	else
	{
		while (n--)
			dest1[n] = src1[n];
	}
	return (dest);
}

// int main(void)
// {
//     char src[] = "BRAQUAGE DE BANQUE";
//     char dest[80];
//     ft_memmove(dest, src, 60);
//     printf("%s\n", dest);
//     return 0;
// }
