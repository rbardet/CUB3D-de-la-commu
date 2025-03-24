/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:15:59 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/21 19:09:44 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char unsigned	*sc1;
	char unsigned	*sc2;

	sc1 = (char unsigned *) s1;
	sc2 = (char unsigned *) s2;
	while (n != 0)
	{
		if (*sc1 != *sc2)
		{
			return (*sc1 - *sc2);
		}
		sc1++;
		sc2++;
		n--;
	}
	return (0);
}
// int main(void)
// {
// 	char chaine1[]="\0";
// 	char chaine2[]="\200";
// 	unsigned int taille = 2;

// 	printf("%d\n", ft_memcmp(chaine1, chaine2, taille));
// 	printf("%d\n", memcmp(chaine1, chaine2, taille));
// }
