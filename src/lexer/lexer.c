/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:31:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/25 11:18:47 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdbool.h>
#include <stdio.h>

void	ft_lexer(const char *line, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_isspace(line[i]))
			ft_lst_add_token(&shell->tokens, ft_if_space(line, &i));
		else if (line[i] == '<' || line[i] == '>')
			ft_lst_add_token(&shell->tokens, ft_if_redi_op(line, &i, shell));
		else if (line[i] == '|')
			ft_lst_add_token(&shell->tokens, ft_if_pipe(line, &i, shell));
		else if (line[i] == '\'')
			ft_lst_add_token(&shell->tokens, ft_if_quot(line, &i, shell));
		else if (line[i] == '\"')
			ft_lst_add_token(&shell->tokens, ft_if_do_quot(line, &i, shell));
		else
			ft_lst_add_token(&shell->tokens, ft_if_word(line, &i));
		if (shell->syn_err_present == true)
			break ;
	}
	merge_tokens(&shell->tokens);
	remove_spaces(&shell->tokens);
}

void	free_token_list(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->token != NULL)
		{
			free(current->token);
		}
		free(current);
		current = next;
	}
}
