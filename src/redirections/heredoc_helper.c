/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:17:44 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/23 13:12:49 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/heredoc.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_append_newline(char *str)
{
	size_t	len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, len + 1);
	new_str[len] = '\n';
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*ft_heredoc_join(char *s1, char *s2)
{
	char	*constr;
	size_t	i;
	size_t	x;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 2;
	constr = (char *)malloc(sizeof(char) * total_len);
	if (!constr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		constr[i] = s1[i];
		i++;
	}
	if (ft_strlen(s1) != 0)
		constr[i++] = '\n';
	x = 0;
	while (s2[x] != '\0')
		constr[i++] = s2[x++];
	constr[i] = '\0';
	free(s1);
	return (constr);
}

int	ft_count_delimiters(t_token *tokens)
{
	t_token	*current;
	int		del_count;

	current = tokens;
	del_count = 0;
	while (current != NULL)
	{
		if (current->type == DLESS)
			del_count++;
		current = current->next;
	}
	return (del_count);
}

char	**ft_extract_delimiters(t_token *tokens)
{
	char		**delimiters;
	const int	len = ft_count_delimiters(tokens);
	int			i;

	delimiters = malloc(sizeof(char *) * (len + 1));
	if (!delimiters)
		return (NULL);
	i = 0;
	while (tokens != NULL)
	{
		if (tokens->type == DLESS)
		{
			if (tokens->next != NULL && tokens->next->type != DLESS
				&& tokens->next->type != LESS && tokens->next->type != GREAT
				&& tokens->next->type != DGREAT)
				delimiters[i++] = tokens->next->token;
			else
				printf("syntax error near unexpected token '<<'\n");
		}
		tokens = tokens->next;
	}
	delimiters[i] = NULL;
	return (delimiters);
}
