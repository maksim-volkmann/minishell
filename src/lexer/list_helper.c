/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:21:13 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/20 16:14:40 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include <stdio.h>

t_token	*ft_new_token(char *str, enum e_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->token = str;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_lst_add_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (*tokens == NULL)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_token;
	return ;
}

void	remove_current_token(t_token **head, t_token **current,
				t_token **previous)
{
	t_token	*temp;

	temp = *current;

	if (*previous == NULL)
		*head = (*current)->next;
	else
		(*previous)->next = (*current)->next;
	*current = (*current)->next;
	free(temp->token);
	free(temp);
}

void	remove_spaces(t_token **head)
{
	t_token	*current;
	t_token	*previous;

	current = *head;
	previous = NULL;
	while (current != NULL)
	{
		if (current->type == SPACES)
			remove_current_token(head, &current, &previous);
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

void	merge_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next_node;
	char	*new_token;

	current = *head;
	while (current != NULL && current->next != NULL)
	{
		next_node = current->next;
		if ((current->type == WORD || current->type == DQUOTE
				|| current->type == QUOTE) && (next_node->type == DQUOTE
				|| next_node->type == WORD || current->type == QUOTE))
		{
			new_token = ft_strjoin(current->token, next_node->token);
			if (!new_token)
				return ;
			free(current->token);
			current->token = new_token;
			current->type = WORD;
			current->next = next_node->next;
			free(next_node->token);
			free(next_node);
		}
		else
			current = current->next;
	}
}