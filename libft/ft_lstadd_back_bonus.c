/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:32:28 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/28 00:35:55 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst1;

	if (!new)
		return ;
	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	lst1 = (*lst);
	while (lst1->next)
		lst1 = lst1->next;
	lst1->next = new;
	return ;
}
// int main(void)
// {
// 	t_list *lst = malloc(sizeof(t_list));
// 	t_list *lst1 = malloc(sizeof(t_list));
// 	t_list *lst2 = malloc(sizeof(t_list));
// 	char str[] = "Argument 1";
// 	char str1[] = "Argument 2";
// 	char str2[] = "Argument 3";
// 	lst->content = str;
// 	lst->next = lst1;
// 	lst1->content = str1;
// 	lst1->next = NULL;
// 	lst2->content = str2;
// 	lst2->next = NULL;
// 	ft_lstadd_back(&lst, lst2);
// 	printf("%s\n", (char *)(lst->content));
// 	printf("%s\n", (char *)(lst->next->content));
// 	printf("%s\n", (char *)(lst->next->next->content));
// 	return 0;
// }
