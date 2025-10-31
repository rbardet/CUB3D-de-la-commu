/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:06:11 by rbardet-          #+#    #+#             */
/*   Updated: 2025/10/11 20:08:05 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(char *s, int c)
{
	char			*str;
	char unsigned	c1;

	str = (char *)s;
	c1 = (char unsigned)c;
	while (*str != '\0')
	{
		if ((char unsigned)*str == c1)
			return (str);
		str++;
	}
	if (c1 == '\0')
		return (str);
	return (NULL);
}
// int main(void)
// {
// 	char str[] = "there is so \0ma\0ny \0 \\0 in t\0his stri\0n";
// 	printf("%s", ft_strchr(str, '\0'));
// 	return(0);
// }
