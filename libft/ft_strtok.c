/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:58 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 15:30:12 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *s, const char *delim)
{
	static char	*next;
	char		*start;

	if (s != NULL)
		next = s;
	if (next == NULL)
		return (NULL);
	while (*next && strchr(delim, *next))
		next++;
	if (*next == '\0')
		return (NULL);
	start = next;
	while (*next && !strchr(delim, *next))
		next++;
	if (*next)
	{
		*next = '\0';
		next++;
	}
	else
		next = NULL;
	return (start);
}
