/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:14:03 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/25 14:04:05 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	test_del(void *content)
// {
// 	free(content);
// }

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*temp;

	if (lst == NULL || *lst == NULL)
		return ;
	temp = *lst;
	head = *lst;
	while (head != NULL)
	{
		temp = temp->next;
		del(head->content);
		free(head);
		head = temp;
	}
	*lst = NULL;
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
// 	ft_lstclear(&node1, test_del);
// }
