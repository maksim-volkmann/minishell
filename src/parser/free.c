/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:40:22 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/06 14:42:22 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_redirection(t_redirection *redir)
{
	if (redir != NULL)
	{
		free(redir);
	}
}

void	free_command(t_command *cmd)

{
	t_command	*current;
	t_command	*next;

	current = cmd;
	while (current != NULL)
	{
		next = current->next;
		if (current->argv != NULL)
		{
			free(current->argv);
		}
		free_redirection(current->input);
		free_redirection(current->output);
		free(current);
		current = next;
	}
}
