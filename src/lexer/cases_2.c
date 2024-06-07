/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:05:33 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/07 11:12:08 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include <stdio.h>

t_token	*ft_if_do_quot(t_token **tokens, const char *line, int *i)
{
	t_token	*new_token;
	char	*token;
	int		start;
	int		end;

	start = (*i);
	(*i)++;
	while (line[*i] != '\0' && line[*i] != '\"')
		(*i)++;
	end = (*i);
	if (line[end] == '\"')
	{
		(*i)++;
		token = ft_extract_str((char *)line, start, end + 1);
		new_token = ft_new_token(token, DQUOTE);
	}
	else
	{
		printf("Error Quote\n");
		return (NULL);
	}
	return (new_token);
}

t_token	*ft_if_and(t_token **tokens, const char *line, int *i)
{
	t_token	*new_token;
	char	*token;
	int		start;
	int		end;

	start = (*i);
	while (line[*i] == '&')
		(*i)++;
	end = (*i);
	token = ft_extract_str((char *)line, *i, *i + 1);
	if (ft_strcmp(token, "&") == 0)
		new_token = ft_new_token(token, AND);
	else if (ft_strcmp(token, "&&") == 0)
		new_token = ft_new_token(token, DAND);
	else
	{
		printf("Error And\n");
		return (NULL);
	}
	return (new_token);
}

t_token *ft_if_word(t_token **tokens, const char *line, int *i)
{
	t_token	*new_token;
	char	*token;
	int		start;
	int		end;

	start = (*i);
	while (line[*i] != '\0')
	{
		if (ft_is_separator(line[*i]) == 1)
			break;
		(*i)++;
	}
	end = (*i);
	token = ft_extract_str((char *)line, start, end);
	if (ft_strcmp(token, "") == 0)
	{
		// printf("Error Word\n");
		free(token);
		return (NULL);
	}
	new_token = ft_new_token(token, WORD);
	return (new_token);
}
