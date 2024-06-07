/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:57:56 by mvolkman          #+#    #+#             */
/*   Updated: 2024/06/07 10:46:54 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_n)
{
	if ((!lst) || (!new_n))
		return ;
	new_n->next = *lst;
	*lst = new_n;
}
