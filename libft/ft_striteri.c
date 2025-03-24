/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 07:37:26 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/23 08:16:01 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int unsigned	a;

	a = 0;
	while (s[a] != '\0')
	{
		(*f)(a, &s[a]);
		a++;
	}
}

// int main(void)
// {
// 	char *strr;
// 	char str[] = "Lille OSC";
// 	strr = ft_strmapi(str, ft_fonction);
// 	printf("%s", strr);
// 	return(0);
// }
