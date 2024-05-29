/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:21:13 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/28 12:12:39 by adrherna         ###   ########.fr       */
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

t_token *ft_lst_add_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (*tokens == NULL)
	{
		*tokens = new_token;
		return (*tokens);
	}
	tmp = *tokens;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_token;
	return (tmp);
}