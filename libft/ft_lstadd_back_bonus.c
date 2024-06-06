/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:20:30 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/06 09:26:58 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_n)
{
	t_list	*ptr;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_n;
		return ;
	}
	ptr = *lst;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = new_n;
}
