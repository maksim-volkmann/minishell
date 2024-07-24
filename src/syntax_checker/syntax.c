/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:24:05 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/24 12:53:39 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include <stdio.h>

int	ft_tokens_size(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	ft_syntax_checker(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == LESS || current->type == DLESS
			|| current->type == GREAT || current->type == DGREAT)
		{
			if (current->next == NULL
				|| current->next->type == LESS
				|| current->next->type == DLESS
				|| current->next->type == GREAT
				|| current->next->type == DGREAT
				|| current->next->type == PIPE)
				return (1);
		}
		if (current->type == PIPE && current->next != NULL
			&&current->next->type == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_syntax_checker_2(t_token *tokens)
{
	t_token		*current;
	int			num_ite;
	const int	lst_size = ft_tokens_size(tokens);

	current = tokens;
	num_ite = 0;
	while (current != NULL)
	{
		if (current->type == PIPE && num_ite == 0)
			return (1);
		if (current->type == PIPE && lst_size == 1)
			return (1);
		current = current->next;
		num_ite++;
	}
	return (0);
}
