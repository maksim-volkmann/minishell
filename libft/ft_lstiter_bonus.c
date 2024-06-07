/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:41:29 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/25 14:00:01 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	f_test(void *content)
// {
// 	int	*intptr;

// 	intptr = (int *)content;
// 	*intptr += 10;
// }

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL)
		return ;
	while (lst->next != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
	f(lst->content);
}

// int	main(void)
// {
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;
// 	int		data1;
// 	int		data2;
// 	int		data3;

// 	data1 = 10;
// 	data2 = 20;
// 	data3 = 30;
// 	node1 = malloc(sizeof(t_list));
// 	node2 = malloc(sizeof(t_list));
// 	node3 = malloc(sizeof(t_list));

// 	node1->content = &data1;
// 	node1->next = node2;

// 	node2->content = &data2;
// 	node2->next = node3;

// 	node3->content = &data3;
// 	node3->next = NULL;
// 	ft_lstiter(node1, f_test);
// }
