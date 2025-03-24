/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:23:14 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/28 00:39:59 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst -> next == NULL)
			return (lst);
		lst = lst -> next;
	}
	return (NULL);
}
// int main(void)
// {
// 	t_list *lst;
// 	t_list *lst1;
// 	t_list *lst2;
// 	char str[] = "Argument 1";
// 	char str1[] = "Argument 2";
// 	char str2[] = "Argument 3";
// 	lst = malloc(sizeof(t_list));
// 	lst1 = malloc(sizeof(t_list));
// 	lst2 = malloc(sizeof(t_list));
// 	lst -> content = str;
// 	lst -> next = lst1;
// 	lst1 -> content = str1;
// 	lst1 -> next = lst2;
// 	lst2 -> content = str2;
// 	lst2 -> next = NULL;
// 	printf("%s\n", (char *)ft_lstlast(lst) -> content);
// 	return(0);
// }
