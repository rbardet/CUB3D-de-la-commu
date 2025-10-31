/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 07:22:27 by rbardet-          #+#    #+#             */
/*   Updated: 2025/10/11 20:08:05 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*src1;
	char	*dest1;
	size_t	a;

	if ((src == NULL) && (dest == NULL))
		return (NULL);
	src1 = (char *)src;
	dest1 = (char *)dest;
	a = 0;
	while (n != 0)
	{
		dest1[a] = src1[a];
		a++;
		n--;
	}
	return (dest);
}
// int main(void)
// {
// 	void *src = NULL;
// 	char *dest = NULL;
// 	ft_memcpy(dest, (const void*)src, 0);
// 	printf("%s\n", (char *)src);
// 	printf("%s", dest);
// 	return(0);
// }
