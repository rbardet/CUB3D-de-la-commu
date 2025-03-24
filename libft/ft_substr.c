/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:13:41 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/23 18:15:06 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_subsubstr(int start, size_t len, char *source, char *str)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (start != 0)
	{
		a++;
		start--;
	}
	while (len != 0)
	{
		str[b] = source[a];
		a++;
		b++;
		len--;
	}
	str[b] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// int main(void)
// {
// 	char str1[] = "Lille OSC";
// 	printf("%s", ft_substr(str1, 0, 5));
// 	return(0);
// }