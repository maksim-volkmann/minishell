/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:17:35 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/31 10:53:38 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"

int main(void)
{
	char	***cmds;
	char	*input;
	t_token	*tokens;

	while (1)
	{
		tokens = NULL;
		input = readline("minishell> ");
		if (input == NULL)
			break;
		ft_lexer(input, &tokens);
		ft_parser(&tokens, cmds);
		free_token_list(tokens);
		free(input);
	}
	return 0;
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
