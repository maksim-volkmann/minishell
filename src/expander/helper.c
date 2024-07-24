/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:26:28 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/24 12:47:04 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

int	ft_var_len(char *input, int i)
{
	int	len;

	len = 0;
	if (input[i + 1] != 0)
		i++;
	while (input[i] != 0)
	{
		if (ft_is_separator_var(input[i] != 0))
			break ;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*ft_join_input(char *s1, char *s2)
{
	char	*constr;
	size_t	i;
	size_t	x;

	if (!s1 || !s2)
		return (NULL);
	constr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!constr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		constr[i] = s1[i];
		i++;
	}
	x = 0;
	while (s2[x] != '\0')
		constr[i++] = s2[x++];
	constr[i] = '\0';
	free(s1);
	return (constr);
}

int	ft_is_separator_var(char c)
{
	int	i;

	i = 0;
	while (NOVAR[i] != '\0')
	{
		if (NOVAR[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup_dq(const char *s)
{
	size_t	len;
	char	*str;

	if (!s)
		return (NULL);
	len = strlen(s);
	str = (char *)malloc(len + 3);
	if (!str)
		return (NULL);
	str[0] = '"';
	ft_strlcpy(str + 1, s, len + 1);
	str[len + 1] = '"';
	str[len + 2] = '\0';
	return (str);
}

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
