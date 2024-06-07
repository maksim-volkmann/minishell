/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:01:41 by mvolkman          #+#    #+#             */
/*   Updated: 2024/06/07 10:46:48 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_n)
{
	t_list	*current;
	t_list	*last;

	current = *lst;
	last = NULL;
	while (current)
	{
		last = current;
		current = current->next;
	}
	if (last)
		last->next = new_n;
	else
		*lst = new_n;
}
