/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:05:33 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/25 18:04:12 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_token	*ft_if_space(const char *line, int *i)
{
	t_token	*new_token;
	char	*token;

	token = ft_strdup(" ");
	while (line[(*i)] != 0 && ft_isspace(line[(*i)]))
	{
		(*i)++;
	}
	new_token = ft_new_token(token, SPACES);
	return (new_token);
}

t_token	*ft_if_do_quot(const char *line, int *i, t_shell *shell)
{
	t_token	*new_token;
	char	*token;
	char	*temp;
	int		start;
	int		end;

	new_token = NULL;
	start = (*i)++;
	while (line[*i] != '\0' && line[*i] != '\"')
		(*i)++;
	end = (*i);
	if (line[end] == '\"')
	{
		(*i)++;
		temp = ft_extract_str((char *)line, start, end + 1);
		token = ft_strtrim(temp, "\"");
		new_token = ft_new_token(token, DQUOTE);
		free(temp);
	}
	else
	{
		shell->syn_err_present = true;
		return (new_token);
	}
	return (new_token);
}

t_token	*ft_if_word(const char *line, int *i)
{
	t_token	*new_token;
	char	*token;
	int		start;
	int		end;

	start = (*i);
	while (line[*i] != '\0')
	{
		if (ft_is_separator(line[*i]) == 1)
			break ;
		(*i)++;
	}
	end = (*i);
	token = ft_extract_str((char *)line, start, end);
	if (ft_strcmp(token, "") == 0)
	{
		free(token);
		return (NULL);
	}
	new_token = ft_new_token(token, WORD);
	return (new_token);
}
