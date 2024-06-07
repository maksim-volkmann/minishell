/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:29:31 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/25 13:31:57 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	test_del(int *content)
// {
// 	free(content);
// }

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*current;
// 	int		*data1;
// 	int		*data2;

// 	data1 = malloc(6 * sizeof(int));
// 	data2 = malloc(6 * sizeof(int));
// 	head = malloc(sizeof(t_list));
// 	current = malloc(sizeof(t_list));

// 	head->content = data1;
// 	head->next = current;

// 	current->content = data2;
// 	current->next = NULL;
// 	ft_lstdelone(head, test_del);
// }
