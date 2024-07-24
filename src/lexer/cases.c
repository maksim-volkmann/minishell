/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:29:48 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/24 12:57:37 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdbool.h>
#include <stdio.h>

t_token	*ft_if_redi_op(const char *line, int *i, t_shell *shell)
{
	t_token	*new_token;
	char	*token;
	int		start;
	int		end;

	start = *i;
	while (line[*i] == '<' || line[*i] == '>')
		(*i)++;
	end = *i;
	token = ft_extract_str((char *)line, start, end);
	if (ft_strcmp(token, ">") == 0)
		new_token = ft_new_token(token, GREAT);
	else if (ft_strcmp(token, "<") == 0)
		new_token = ft_new_token(token, LESS);
	else if (ft_strcmp(token, ">>") == 0)
		new_token = ft_new_token(token, DGREAT);
	else if (ft_strcmp(token, "<<") == 0)
		new_token = ft_new_token(token, DLESS);
	else
	{
		shell->syn_err_present = true;
		return (NULL);
	}
	return (new_token);
}

t_token	*ft_if_pipe(const char *line, int *i, t_shell *shell)
{
	t_token	*new_token;
	char	*token;
	int		start;
	int		end;

	start = *i;
	new_token = NULL;
	while (line[*i] == '|')
		(*i)++;
	end = *i;
	token = ft_extract_str((char *)line, start, end);
	if (ft_strcmp(token, "|") == 0)
		new_token = ft_new_token(token, PIPE);
	else
	{
		shell->syn_err_present = true;
		return (new_token);
	}
	return (new_token);
}

t_token	*ft_if_par(const char *line, int *i)
{
	t_token	*new_token;
	char	*token;
	int		start;
	int		end;

	start = *i;
	while (line[*i] == '(' || line[*i] == ')')
		(*i)++;
	end = *i;
	token = ft_extract_str((char *)line, start, end);
	if (ft_strcmp(token, "(") == 0)
		new_token = ft_new_token(token, LPAR);
	else if (ft_strcmp(token, ")") == 0)
		new_token = ft_new_token(token, RPAR);
	else
	{
		printf("Error Parenthesis\n");
		return (NULL);
	}
	return (new_token);
}

t_token	*ft_if_quot(const char *line, int *i)
{
	t_token	*new_token;
	char	*temp;
	char	*token;
	int		start;
	int		end;

	start = (*i);
	(*i)++;
	while (line[*i] != '\0' && line[*i] != '\'')
		(*i)++;
	end = (*i);
	if (line[end] == '\'')
	{
		(*i)++;
		temp = ft_extract_str((char *)line, start, end + 1);
		token = ft_strtrim(temp, "\'");
		new_token = ft_new_token(token, QUOTE);
		free(temp);
	}
	else
	{
		printf("Error Quote\n");
		return (NULL);
	}
	return (new_token);
}
