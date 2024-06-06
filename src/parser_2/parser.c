/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:52 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/06 11:26:29 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void print_redirection(t_redirection *redir)
{
	while (redir != NULL)
	{
		printf("Type: %d, File: %s\n", redir->type, redir->file);
		redir = redir->next;
	}
}

void print_command(t_command *cmd)
{
	int i;

	if (cmd == NULL)
	{
		printf("Command is NULL\n");
		return;
	}

	printf("Arguments: ");
	for (i = 0; cmd->argv && cmd->argv[i]; i++)
	{
		printf("%s ", cmd->argv[i]);
	}
	printf("\n");

	printf("Output redirections:\n");
	print_redirection(cmd->output);

	printf("Input redirections:\n");
	print_redirection(cmd->input);
}

void	ft_parser(t_command **cmds, t_token **tokens)
{
	t_token		*current;
	t_command	*new;
	int			i;

	current = (*tokens);
	i = 0;
	while (current != NULL)
	{
		new = ft_new_node();
		new->argv = ft_get_darray(tokens);
		new->output = ft_fill_output(new->argv);
		print_command(new);
		current = current->next;
	}
}
