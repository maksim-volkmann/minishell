/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:17:35 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/06 10:34:41 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"
#include <stdlib.h>

void	leaks(void)
{
	system("leaks minishell_2");
}

int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_command	*cmds;

	// atexit(leaks);
	while (1)
	{
		cmds = NULL;
		tokens = NULL;
		input = readline("minishell> ");
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			break ;
		}
		ft_lexer(input, &tokens);
		ft_parser(&cmds, &tokens);
		//TODO: pipex part called here.
		free_token_list(tokens);
		free(input);
	}
	return (0);
}

		// print_cmd_list(cmds);
		// print_linked_list(tokens);

// ver si puedo implementar una history
// ver que es expand

// 3.1.2.3 Double Quotes
// Enclosing characters in double quotes
// (‘"’) preserves the literal value of all characters
//  within the quotes, with the exception of ‘$’, ‘`’, ‘\’

// Tilde Expansion:

// Expands the tilde character (~) to the value of the home directory. For example, ~ expands to /home/username.
// Parameter and Variable Expansion:

// Replaces variables with their values. For example, $HOME expands to /home/username.
// Can also include modifiers, such as ${VAR:-default}, which provides a default value if the variable is unset.
