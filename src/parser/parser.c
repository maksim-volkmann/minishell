/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:31:19 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/03 09:45:57 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdio.h>

void ft_print_cmds(char ***cmds)
{
	int i, j;

	i = 0;
	while (cmds[i] != NULL)
	{
		printf("Command %d: ", i + 1);
		j = 0;
		while (cmds[i][j] != NULL)
		{
			printf("[%d]\"%s\" ", j, cmds[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

char	***ft_cmds_malloc(t_token	**tokens)
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

void	ft_extract_cmd(t_token **tokens, char ***cmds)
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
		cmds[i] = (char **)malloc(sizeof(char *) * (j + 1));
		if (cmds[i] == NULL)
			return ;
		cmds[i][j] = NULL;
		i++;
		if (current != NULL)
			current = current->next;
	}
	cmds[i] = NULL;
}

void	ft_fill_array(t_token **tokens, char ***cmds)
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
			cmds[i][j] = current->token;
			j++;
			current = current->next;
		}
		cmds[i][j] = NULL;
		i++;
		if (current != NULL && current->type == PIPE)
			current = current->next;
	}
}

void	ft_parser(t_token **tokens, char ***cmds)
{
	t_token	*current;

	current = *tokens;
	if (current == NULL)
		return ;
	cmds = ft_cmds_malloc(tokens);
	ft_extract_cmd(tokens, cmds);
	ft_fill_array(tokens, cmds);
	ft_print_cmds(cmds);
}
