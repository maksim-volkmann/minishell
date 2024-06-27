/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:58:01 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/27 14:27:54 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*ft_extract_str(char *line, int start, int end)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (end - start + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = line[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_is_separator(char c)
{
	int	i;

	i = 0;
	while (NOWORD[i] != '\0')
	{
		if (NOWORD[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
	{
		return (1);
	}
	return (0);
}
