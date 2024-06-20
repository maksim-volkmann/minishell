/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:29:48 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/20 15:33:12 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

// This function is called when a redirection op is found
// It extracts the token and returns it

t_token	*ft_if_redi_op(const char *line, int *i)
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

t_token	*ft_if_pipe(const char *line, int *i)
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
	// char	*temp;
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
		// token = ft_strtrim(temp, "\'");
		if (ft_strcmp(token, "") == 0)
			return (NULL);
		new_token = ft_new_token(token, QUOTE);
		// free(temp);
	}
	else
	{
		printf("Error Quote\n");
		return (NULL);
	}
	return (new_token);
}
