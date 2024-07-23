/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:56:09 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/23 13:12:22 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_cmd	*ft_new_node(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->output = malloc(sizeof(t_redir));
	new->input = malloc(sizeof(t_redir));
	if (!new->input || !new->output)
		return (NULL);
	new->input->file = NULL;
	new->output->file = NULL;
	new->input->type = REDIR_NONE;
	new->output->type = REDIR_NONE;
	new->next = NULL;
	return (new);
}

void	add_or_init_node(t_cmd **cmds, t_cmd *new_n)
{
	t_cmd	*current;

	if (*cmds == NULL)
	{
		*cmds = new_n;
		new_n->next = NULL;
		return ;
	}
	current = *cmds;
	while (current->next != NULL)
		current = current->next;
	current->next = new_n;
	new_n->next = NULL;
}
