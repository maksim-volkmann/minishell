/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:52 by adrherna          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/28 16:55:38 by mvolkman         ###   ########.fr       */
=======
/*   Updated: 2024/06/28 13:34:02 by adrherna         ###   ########.fr       */
>>>>>>> 27ca365a837972f80b8fd7f1cde9e35a1b80c385
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>

void	assign_to_darray(char **src, char **darray, int *i, int *j)
{
	size_t const	len = ft_strlen(src[*i]) + 1;

	darray[*j] = (char *)malloc(len * sizeof(char));
	ft_strlcpy(darray[*j], src[*i], len);
	(*i)++;
	(*j)++;
}

// void	ft_parser(t_shell *shell, t_token **tokens)
// {
// 	t_token		*current;
// 	t_command	*new;

// 	current = *tokens;
// 	while (current != NULL)
// 	{
// 		if (current->type == PIPE)
// 			current = current->next;
// 		new = ft_new_node();
// 		new->argv = ft_get_darray(&current, &shell, new->input, new->output);
// 		add_or_init_node(&shell->cmds, new);
// 		// print_command(new);
// 	}
// }

void ft_parser(t_shell *shell, t_token **tokens)
{
	t_token     *current;
	t_command   *new;

	current = *tokens;
	while (current != NULL)
	{
		if (current->type == PIPE)
			current = current->next;
		new = ft_new_node();
		new->argv = ft_get_darray(&current, &shell, new->input, new->output);
		// If no arguments, new->argv is already NULL
		add_or_init_node(&shell->cmds, new);
		// print_command(new);
	}
}




// revisar que el file despues de un redir op no sea |

// echo hola >> text1.txt >> text2.txt | echo telo > text3.txt

// new->argv = NULL
