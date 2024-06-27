/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:31:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/27 15:35:06 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include <stdio.h>

void	ft_lexer(const char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		// printf("helo\n");
		if (ft_isspace(line[i]))
			ft_lst_add_token(tokens, ft_if_space(line, &i));
		else if (line[i] == '<' || line[i] == '>')
			ft_lst_add_token(tokens, ft_if_redi_op(line, &i));
		else if (line[i] == '|')
			ft_lst_add_token(tokens, ft_if_pipe(line, &i));
		else if (line[i] == '(' || line[i] == ')')
			ft_lst_add_token(tokens, ft_if_par(line, &i));
		else if (line[i] == '\'')
			ft_lst_add_token(tokens, ft_if_quot(line, &i));
		else if (line[i] == '\"')
			ft_lst_add_token(tokens, ft_if_do_quot(line, &i));
		else if (line[i] == '&')
			ft_lst_add_token(tokens, ft_if_and(line, &i));
		else
			ft_lst_add_token(tokens, ft_if_word(line, &i));
	}
	merge_tokens(tokens);
	remove_spaces(tokens);
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
