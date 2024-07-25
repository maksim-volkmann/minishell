/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:46:42 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/25 17:30:54 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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

char	**ft_allocate_darray(t_token **tokens)
{
	int		size;
	char	**darray;

	size = ft_darray_size((*tokens));
	darray = NULL;
	if (size == 0)
		return (NULL);
	darray = malloc(sizeof(char *) * (size + 1));
	if (!darray)
		return (NULL);
	return (darray);
}

void	ft_populate_darray(t_token **tokens, char **darray,
						t_redir *input, t_redir *output)
{
	int	i;

	i = 0;
	while ((*tokens) != NULL && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == DGREAT || (*tokens)->type == GREAT
			|| (*tokens)->type == LESS || (*tokens)->type == DLESS)
		{
			ft_handle_redir((*tokens), input, output);
			if ((*tokens)->next == NULL)
			{
				(*tokens) = (*tokens)->next;
				continue ;
			}
			else
			{
				(*tokens) = (*tokens)->next->next;
				continue ;
			}
		}
		darray[i] = (*tokens)->token;
		i++;
		(*tokens) = (*tokens)->next;
	}
	darray[i] = NULL;
}

char	**ft_get_darray(t_token **tokens, t_redir *input,
					t_redir *output)
{
	char	**darray;

	darray = ft_allocate_darray(tokens);
	if (!darray)
		return (NULL);
	ft_populate_darray(tokens, darray, input, output);
	return (darray);
}
