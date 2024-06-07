/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:52 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/06 14:18:33 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdio.h>

void print_redirection(t_redirection *redir)
{
	while (redir != NULL)
	{
		printf("Type: %d, File: %s\n", redir->type, redir->file);
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

	current = *tokens;
	while (current != NULL)
	{
		if (current->type == PIPE)
			current = current->next;
		new = ft_new_node();
		new->argv = ft_get_darray(&current);
		new->output = ft_fill_output(new->argv);
		new->input = ft_fill_input(new->argv);
		add_or_init_node(cmds, new);
		// print_command(new);
	}
}


// revisar que el file despues de un redir op no sea |

// echo hola >> text1.txt >> text2.txt | echo telo > text3.txt