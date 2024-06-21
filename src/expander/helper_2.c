/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:49:08 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/21 11:35:41 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include <sys/_types/_null.h>

char	*ft_quote_string(char *input)
{
	size_t	length;
	char	*quoted_string;

	length = strlen(input);
	quoted_string = (char *)malloc(length + 3);
	if (quoted_string == NULL)
		return (NULL);
	quoted_string[0] = '\"';
	ft_strlcpy(quoted_string + 1, input, length + 1);
	quoted_string[length + 1] = '\"';
	quoted_string[length + 2] = '\0';
	free(input);
	return (quoted_string);
}

char	*ft_extract_segment_dq(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	start = *i;
	while (input[*i] != '\0' && input[*i] != '$' && input[*i] != '\"')
	{
		(*i)++;
	}
	end = *i;
	if (end > start)
	{
		segment = ft_extract_str(input, start, end);
		return (segment);
	}
	else
	{
		return (NULL);
	}
}

char	*ft_segment_helper(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	start = *i;
	while (input[*i] != '\0' && input[*i] != '$' && input[*i] != '\"'
		&& input[*i] != '\'')
	{
		(*i)++;
	}
	end = *i;
	if (end > start)
	{
		segment = ft_extract_str(input, start, end);
		return (segment);
	}
	else
	{
		return (NULL);
	}
}
