/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:05:33 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/28 15:06:53 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../libft/libft.h"

t_token *ft_if_do_quot(t_token **tokens, const char *line, int *i)
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
		new_token = ft_new_token(token, QUOTE);
	}
	else
	{
		printf("Error Quote\n");
		return NULL;
	}
	return (new_token);
}