/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 05:53:32 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/28 00:39:10 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if ((!lst) || !(f))
		return ;
	while (lst != NULL)
	{
		f(lst ->content);
		lst = lst -> next;
	}
	return ;
}
// void ft_iter(void *content)
// {
// 	content = "ZZZ";
// 	printf("%s\n", (char *)content);
// }

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
// 	ft_lstiter(lst, ft_iter);
// 	return(0);
// }
