/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:08:57 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/25 12:22:00 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_finder(const char *s, int start, char sep)
{
	int	len;

	len = 0;
	while (s[start] != sep && s[start] != 0)
		start++;
	return (start);
}

static int	ft_strs_counter(char const *s, char c)
{
	int	on_off;
	int	strs_counter;

	strs_counter = 0;
	on_off = 1;
	while (*s != '\0')
	{
		if (*s == c)
		{
			on_off = 1;
			s++;
		}
		else if (on_off == 1 && *s != c)
		{
			strs_counter++;
			on_off = 0;
			s++;
		}
		else
			s++;
	}
	return (strs_counter);
}

static int	ft_insert_str(const char *str, int start, int len, char **new_str)
{
	int		i;

	if (len == 0)
		return (0);
	*new_str = (char *)malloc(len + 1);
	if (!(*new_str))
		return (-1);
	i = 0;
	while (len > 0)
	{
		(*new_str)[i] = str[start];
		i++;
		start++;
		len--;
	}
	(*new_str)[i] = 0;
	return (1);
}

static char	**free_array(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
		free(strings[i++]);
	free(strings);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**strings;
	size_t		start;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	start = 0;
	strings = (char **)ft_calloc((ft_strs_counter(s, c) + 1), sizeof (char *));
	if (!strings)
		return (0);
	while (s[j] != 0)
	{
		while (s[j] == c && s[j] != 0)
			j++;
		start = j;
		j = ft_len_finder(s, j, c);
		if (ft_insert_str(s, start, j - start, strings + i) == -1)
			return (free_array(strings));
		start = j;
		i++;
	}
	return (strings);
}

// int	main(void)
// {
// 	char	*str = "hg au do";
// 	char	**strings = ft_split(str, ' ');
// 	return (0);
// }
