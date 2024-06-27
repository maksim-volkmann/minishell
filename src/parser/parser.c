/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:52 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/26 14:43:27 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>

// int	get_size(char **src)
// {
// 	int	size;

// 	size = 0;
// 	while (src[size] != NULL)
// 		size++;
// 	return (size);
// }

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
	t_token		*current;
	t_command	*new;

	current = *tokens;
	while (current != NULL)
	{
		if (current->type == PIPE)
			current = current->next;
		new = ft_new_node();
		new->argv = ft_get_darray(&current, &shell, new->input, new->output);
		add_or_init_node(&shell->cmds, new);
		// print_command(new);
	}
}

// revisar que el file despues de un redir op no sea |

// echo hola >> text1.txt >> text2.txt | echo telo > text3.txt