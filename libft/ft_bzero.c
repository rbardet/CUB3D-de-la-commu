/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:58:37 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/22 12:58:15 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n != 0)
	{
		*str = 0;
		str++;
		n--;
	}
}
// int main(void)
// {
// 	void *str = "Losc";
// 	ft_bzero(str, 2);
// 	printf("%s\n", (char *)str);
// 	return(0);
// }
