/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:57:11 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/26 14:01:44 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*f_test(void *content)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = (char *)content;
// 	content = (char *)content;
// 	while (str[i] != 0)
// 	{
// 		str[i] -= 32;
// 		i++;
// 	}
// 	return (content);
// }

// void	del(void *content)
// {
// 	free(content);
// }

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*current;
	void	*temp;

	head = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		temp = f(lst->content);
		current = ft_lstnew(temp);
		if (!current)
		{
			del(temp);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, current);
		lst = lst->next;
	}
	return (head);
}

// int	main(void)
// {
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	char data1[5] = "hola";
// 	char data2[4] = "que";
// 	char data3[6] = "haces";
// 	node1 = malloc(sizeof(t_list));
// 	node2 = malloc(sizeof(t_list));
// 	node3 = malloc(sizeof(t_list));

// 	node1->content = &data1;
// 	node1->next = node2;

// 	node2->content = &data2;
// 	node2->next = node3;

// 	node3->content = &data3;
// 	node3->next = NULL;

// 	t_list	*result = ft_lstmap(node1, f_test, del);

// 	t_list *temp = result;
// 	while (result->next != NULL)
// 	{
// 		printf("%s\n", (char *)temp->content);
// 		temp = temp->next;
// 	}
// }
