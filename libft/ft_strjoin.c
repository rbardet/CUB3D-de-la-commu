/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 07:45:34 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/21 19:11:45 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strleng(char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
		a++;
	return (a);
}

// static char	*ft_malloc(int n, int n2)
// {
// 	char	*str;

// 	str = malloc(sizeof(char) * (n + n2 + 1));
// 	if (!str)
// 		return (NULL);
// 	return (str);
// }

char	*ft_subjoin(char *s1, char *s2, char *s3)
{
	int		c;
	int		d;

	c = 0;
	d = 0;
	while (s1[c] != '\0')
	{
		s3[c + d] = s1[c];
		c++;
	}
	while (s2[d] != '\0')
	{
		s3[c + d] = s2[d];
		d++;
	}
	s3[c + d] = '\0';
	return (s3);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		a;
	int		b;

	a = ft_strleng((char *)s1);
	b = ft_strleng((char *)s2);
	if (s1 == 0 || s2 == 0)
		return (NULL);
	s3 = malloc(sizeof(char) * (a + b + 1));
	if (!s3)
		return (NULL);
	s3 = ft_subjoin(s1, s2, s3);
	return (s3);
}
// int main(void)
// {
// 	char str1[] = "LILLE";
// 	char str2[] = " OSC";
// 	printf("%s", ft_strjoin(str1, str2));
// 	return(0);
// }
