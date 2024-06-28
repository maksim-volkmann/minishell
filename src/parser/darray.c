/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:46:42 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/28 16:55:22 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdio.h>

int	ft_darray_size(t_token	*tokens)
{
	t_token	*current;
	int		i;

	current = (tokens);
	i = 0;
	while (current != NULL && current->type != PIPE)
	{
		i++;
		current = current->next;
	}
	return (i);
}

// char	**ft_get_darray(t_token **tokens, t_shell **shell, t_redirection *input, t_redirection *output)
// {
// 	char	**darray;
// 	int		size;
// 	int		i;

// 	size = ft_darray_size((*tokens));
// 	i = 0;
// 	darray = malloc(sizeof(char *) * (size + 1));
// 	if (!darray)
// 		return (NULL);
// 	while ((*tokens) != NULL && (*tokens)->type != PIPE)
// 	{
// 		if ((*tokens)->type == DGREAT || (*tokens)->type == GREAT
// 			|| (*tokens)->type == LESS || (*tokens)->type == DLESS)
// 		{
// 			ft_handle_redir((*tokens), (*shell), input, output);
// 			(*tokens) = (*tokens)->next->next;
// 			continue ;
// 		}
// 		darray[i] = (*tokens)->token;
// 		i++;
// 		(*tokens) = (*tokens)->next;
// 	}
// 	darray[i] = NULL;
// 	return (darray);
// }

char **ft_get_darray(t_token **tokens, t_shell **shell, t_redirection *input, t_redirection *output)
{
	char **darray;
	int size;
	int i;

	size = ft_darray_size((*tokens));
	if (size == 0)  // If no arguments, return NULL
		return (NULL);

	i = 0;
	darray = malloc(sizeof(char *) * (size + 1));
	if (!darray)
		return (NULL);
	while ((*tokens) != NULL && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == DGREAT || (*tokens)->type == GREAT
			|| (*tokens)->type == LESS || (*tokens)->type == DLESS)
		{
			ft_handle_redir((*tokens), (*shell), input, output);
			(*tokens) = (*tokens)->next->next;
			continue ;
		}
		darray[i] = (*tokens)->token;
		i++;
		(*tokens) = (*tokens)->next;
	}
	darray[i] = NULL;

	return (darray);
}

