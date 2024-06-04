/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tarray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:37:15 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/04 09:49:12 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	***ft_tarray_malloc(t_token	**tokens)
{
	t_token	*current;
	char	***cmds;
	int		pipe_count;

	pipe_count = 0;
	current = *tokens;
	while (current->next != NULL)
	{
		if (current->type == PIPE)
			pipe_count++;
		current = current->next;
	}
	cmds = (char ***)malloc(sizeof(char **) * (pipe_count + 2));
	if (cmds == NULL)
		return (NULL);
	cmds[pipe_count + 1] = NULL;
	return (cmds);
}

void	ft_extract_cmd(t_token **tokens, char ***tarray)
{
	t_token	*current;
	int		i;
	int		j;

	i = 0;
	current = *tokens;
	while (current != NULL)
	{
		j = 0;
		while (current != NULL && current->type != PIPE)
		{
			current = current->next;
			j++;
		}
		tarray[i] = (char **)malloc(sizeof(char *) * (j + 1));
		if (tarray[i] == NULL)
			return ;
		tarray[i][j] = NULL;
		i++;
		if (current != NULL)
			current = current->next;
	}
	tarray[i] = NULL;
}

void	ft_fill_array(t_token **tokens, char ***tarray)
{
	t_token	*current;
	int		i;
	int		j;

	current = *tokens;
	i = 0;
	while (current != NULL)
	{
		j = 0;
		while (current != NULL && current->type != PIPE)
		{
			tarray[i][j] = current->token;
			j++;
			current = current->next;
		}
		tarray[i][j] = NULL;
		i++;
		if (current != NULL && current->type == PIPE)
			current = current->next;
	}
}

void	ft_tarray(t_token **tokens, char ***tarray)
{
	t_token	*current;

	current = *tokens;
	if (current == NULL)
		return ;
	tarray = ft_tarray_malloc(tokens);
	ft_extract_cmd(tokens, tarray);
	ft_fill_array(tokens, tarray);
	ft_print_cmds(tarray);
}
