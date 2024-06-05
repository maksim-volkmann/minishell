/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:56:09 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/05 15:23:57 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>

t_command	*ft_new_node(char **cmd)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->argv = cmd;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	return (new);
}

void add_or_init_node(t_command **cmds, t_command *new_n)
{
	t_command *current;

	if (*cmds == NULL)
	{
		*cmds = new_n;
		new_n->next = NULL;
		return;
	}

	current = *cmds;
	while (current->next != NULL)
		current = current->next;
	current->next = new_n;
	new_n->next = NULL;
}
