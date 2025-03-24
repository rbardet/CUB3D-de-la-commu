/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:39:12 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/24 08:02:19 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	a;

	a = 0;
	while (lst)
	{
		lst = lst -> next;
		a++;
	}
	return (a);
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
