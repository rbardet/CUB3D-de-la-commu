/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:46:53 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/28 00:38:18 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst1;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		lst1 = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = lst1;
	}
	*lst = NULL;
	return ;
}

// void ft_lstdelonee(void *content)
// {
// 	return ;
// }

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
// 	lst1->next = lst2;
// 	lst2->content = str2;
// 	lst2->next = NULL;

// 	ft_lstclear(&lst, (void*)ft_lstdelonee);
// 	if (lst == NULL)
// 		printf("C'est bon");
// 	return 0;
// }
