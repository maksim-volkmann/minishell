/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:55 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/24 12:47:20 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*ft_handle_single_quote(char *input, int *index, char *exp_input)
{
	char	*temp;
	char	*new_exp_input;

	temp = ft_extract_sq(input, index);
	new_exp_input = ft_join_input(exp_input, temp);
	free(temp);
	return (new_exp_input);
}

char	*ft_extract_sq(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	start = (*i);
	(*i)++;
	while (input[(*i)] != 0 && input[(*i)] != '\'')
		(*i)++;
	if (input[*i] == '\'' && input[(*i) + 1] != 0)
		(*i)++;
	end = (*i);
	segment = ft_extract_str(input, start, end);
	return (segment);
}
