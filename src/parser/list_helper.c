/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:56:09 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/04 10:11:26 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>

t_command	*ft_new_node(char **cmd)
{
	t_command	*new_n;

	new_n = malloc(sizeof(t_command));
	if (!new_n)
		return (NULL);
	new_n->argv = cmd;
	new_n->next = NULL;
	return (new_n);
}

void	add_or_init_node(t_command **cmds, t_command *new_n)
{
	t_command	*current;

	if (*cmds == NULL)
	{
		*cmds = new_n;
		return ;
	}
	current = (*cmds);
	while (current != NULL)
		current = current->next;
	current->next = new_n;
}
