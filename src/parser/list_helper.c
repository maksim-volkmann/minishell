/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:56:09 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/26 10:09:50 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <sys/_types/_null.h>

t_command	*ft_new_node(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->output = malloc(sizeof(t_redirection));
	new->input = malloc(sizeof(t_redirection));
	if (!new->input || !new->output)
		return (NULL);
	new->input->file = NULL;
	new->output->file = NULL;
	new->input->type = REDIR_NONE;
	new->output->type = REDIR_NONE;
	new->next = NULL;
	return (new);
}

void	add_or_init_node(t_command **cmds, t_command *new_n)
{
	t_command	*current;

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
