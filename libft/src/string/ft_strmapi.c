/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:18:45 by rbardet-          #+#    #+#             */
/*   Updated: 2025/10/11 20:08:05 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strleng(char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
		a++;
	return (a);
}

// static char	ft_fonction(unsigned int a, char b)
// {
// 	return (a + b);
// }

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	unsigned int	a;
	int				longueur;
	char			*str;

	a = 0;
	longueur = ft_strleng(s);
	str = malloc(sizeof(char) * (longueur + 1));
	if (!str)
		return (NULL);
	while (longueur != 0)
	{
		str[a] = (*f)(a, s[a]);
		a++;
		longueur--;
	}
	str[a] = '\0';
	return (str);
}
// int main(void)
// {
// 	char *strr;
// 	char str[] = "Lille OSC";
// 	strr = ft_strmapi(str, ft_fonction);
// 	printf("%s", strr);
// 	return(0);
// }
