/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:17:35 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/30 16:55:53 by adrherna         ###   ########.fr       */
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
		// print_linked_list(tokens);
		// print_cmd_list(cmds);
		free_token_list(tokens);
		free(input);
	}
	return 0;
}

// seg fault with empty readline