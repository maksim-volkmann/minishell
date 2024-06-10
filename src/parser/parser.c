/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:52 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/08 13:59:13 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_redirection_operator(const char *str)
{
	const char	*redirection_operators[] = {">", ">>", "<", "<<", NULL};
	int			i;

	i = 0;
	while (redirection_operators[i] != NULL)
	{
		if (strcmp(str, redirection_operators[i]) == 0)
			return (1);
		i++;
	}

	return (0);
}

int	get_size(char **src)
{
	int	size;

	size = 0;
	while (src[size] != NULL)
		size++;
	return (size);
}


void	assign_to_darray(char **src, char **darray, int *i, int *j)
{
	size_t const	len = ft_strlen(src[*i]) + 1;

	darray[*j] = (char *)malloc(len * sizeof(char));
	ft_strlcpy(darray[*j], src[*i], len);
	(*i)++;
	(*j)++;
}

char	**ft_clean_darray(char **src)
{
	int const	size = get_size(src);
	char		**darray;
	int			i;
	int			j;

	i = 0;
	j = 0;
	darray = (char **)malloc(sizeof(char *) * (size + 1));
	while (src[i] != NULL)
	{
		if (is_redirection_operator(src[i]))
		{
			if (src[i + 1] != NULL)
				i += 2;
			else
				break ;
		}
		else
			assign_to_darray(src, darray, &i, &j);
	}
	darray[j] = NULL;
	return (darray);
}

void	ft_parser(t_command **cmds, t_token **tokens)
{
	t_token		*current;
	t_command	*new;

	current = *tokens;
	while (current != NULL)
	{
		if (current->type == PIPE)
			current = current->next;
		new = ft_new_node();
		new->argv = ft_get_darray(&current);
		new->output = ft_fill_output(new->argv);
		new->input = ft_fill_input(new->argv);
		new->argv = ft_clean_darray(new->argv);
		add_or_init_node(cmds, new);
		// print_command(new);
	}
}


// revisar que el file despues de un redir op no sea |

// echo hola >> text1.txt >> text2.txt | echo telo > text3.txt