/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:29:48 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/28 13:39:26 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../libft/libft.h"
#include <stdio.h>

// This function is called when a redirection op is found
// It extracts the token and returns it

t_token	*ft_if_redi_op(t_token **tokens, const char *line, int *i)
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
		printf("Error Redirector\n");
		return (NULL);
	}
	return (new_token);
}

t_token	*ft_if_pipe(t_token **tokens, const char *line, int *i)
{
	t_token	*new_token;
	char	*token;
	int		start;
	int		end;

	start = *i;
	while (line[*i] == '|')
		(*i)++;
	end = *i;
	token = ft_extract_str((char *)line, start, end);
	if (ft_strcmp(token, "|") == 0)
		new_token = ft_new_token(token, PIPE);
	else
	{
		printf("Error Pipe\n");
		return (NULL);
	}
	return (new_token);
}

t_token	*ft_if_par(t_token **tokens, const char *line, int *i)
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

t_token *ft_if_quot(t_token **tokens, const char *line, int *i)
{
	t_token	*new_token;
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
		token = ft_extract_str((char *)line, start, end + 1);
		new_token = ft_new_token(token, QUOTE);
	}
	else
	{
		printf("Error Quote\n");
		return NULL;
	}
	return (new_token);
}