/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:40:22 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/25 17:31:11 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_redirection(t_redir *redir)
{
	if (redir != NULL)
	{
		free(redir);
	}
}

void	free_command(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

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

void	ft_free_heredoc(char *content, char **delimiters)
{
	free(content);
	free(delimiters);
}
