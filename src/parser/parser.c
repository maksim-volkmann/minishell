/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:30:28 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/25 17:50:49 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	assign_to_darray(char **src, char **darray, int *i, int *j)
{
	size_t const	len = ft_strlen(src[*i]) + 1;

	darray[*j] = (char *)malloc(len * sizeof(char));
	ft_strlcpy(darray[*j], src[*i], len);
	(*i)++;
	(*j)++;
}

void	ft_parser(t_shell *shell, t_token **tokens)
{
	t_token	*current;
	t_cmd	*new;

	current = *tokens;
	while (current != NULL)
	{
		if (current->type == PIPE)
			current = current->next;
		new = ft_new_node();
		new->argv = ft_get_darray(&current, new->input, new->output);
		add_or_init_node(&shell->cmds, new);
	}
}
