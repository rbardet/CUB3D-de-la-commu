/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:08:17 by rbardet-          #+#    #+#             */
/*   Updated: 2024/10/28 00:36:16 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if ((!*lst) && (!new))
		return ;
	new->next = *lst;
	*lst = new;
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
// 	ft_lstadd_front(&lst, lst2);
// 	printf("%s\n", (char *)(lst->content));
// 	printf("%s\n", (char *)(lst->next->content));
// 	printf("%s\n", (char *)(lst->next->next->content));
// 	return 0;
// }
