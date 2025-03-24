/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:01:26 by rbardet-          #+#    #+#             */
/*   Updated: 2024/11/08 04:28:23 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	ft_printf_prc(void)
{
	write(1, "%", 1);
	return (1);
}
// int main(void)
// {
// 	ft_printf_prc;
// 	return(0);
// }
