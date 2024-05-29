/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:31:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/29 10:32:44 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	ft_get_tokens(const char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' || line[i] == '>')
			ft_lst_add_token(tokens, ft_if_redi_op(tokens, line, &i));
		else if (line[i] == '|')
			ft_lst_add_token(tokens, ft_if_pipe(tokens, line, &i));
		else if (line[i] == '(' || line[i] == ')')
			ft_lst_add_token(tokens, ft_if_par(tokens, line, &i));
		else if (line[i] == '\'')
			ft_lst_add_token(tokens, ft_if_quot(tokens, line, &i));
		else if (line[i] == '\"')
			ft_lst_add_token(tokens, ft_if_do_quot(tokens, line, &i));
		else
			i++;
	}
}

void free_token_list(t_token *head)
{
	t_token *current;
	t_token *next;

	current = head;

	while (current != NULL) {
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
}

void print_linked_list(t_token *head)
{
	t_token *current = head;

	while (current != NULL) {
		printf("Token: %s, Type: %d\n", current->token, current->type);
		current = current->next;
	}
}