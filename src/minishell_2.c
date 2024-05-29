/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:17:35 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/29 10:33:32 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		tokens = NULL;
		input = readline("minishell> ");
		if (input == NULL) {
			break;
		}
		ft_get_tokens(input, &tokens);
		print_linked_list(tokens);
		free_token_list(tokens);
		free(input);
	}
	return 0;
}