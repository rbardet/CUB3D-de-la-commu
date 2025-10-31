/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:30:39 by rbardet-          #+#    #+#             */
/*   Updated: 2025/10/11 20:08:05 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[a] && a < len)
	{
		if (big[a] == little[0])
		{
			b = 0;
			while (little[b] && (a + b) < len && big[a + b] == little[b])
			{
				b++;
			}
			if (little[b] == '\0')
				return ((char *)&big[a]);
		}
		a++;
	}
	return (NULL);
}

// int main(void)
// {
// 	char big[] = "LILLE OSC";
// 	char little[] = "ILL";
// 	printf("%s\n", ft_strnstr(big, little, 4));
// 	return(0);
// }
