/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:56:09 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/22 12:58:56 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <sys/_types/_null.h>

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
