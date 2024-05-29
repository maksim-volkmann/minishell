/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 08:40:07 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/23 15:21:39 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_start(char const *s1, char const *set, int s1_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != 0 && i <= s1_len)
	{
		while (set[j] != 0)
		{
			if (s1[i] == set[j])
			{
				i++;
				j = 0;
				continue ;
			}
			j++;
		}
		if (set[j] == 0 && i != s1_len)
			return (i);
		i++;
		j = 0;
	}
	if (i > s1_len)
		return (0);
	return (i);
}

static int	ft_find_end(char const *s1, char const *set, int s1_len)
{
	int	i;

	i = 0;
	while (s1_len - 1 > 0)
	{
		while (set[i] != 0)
		{
			if (s1[s1_len - 1] == set[i])
			{
				s1_len--;
				i = 0;
				continue ;
			}
			i++;
		}
		if (set[i] == 0 && s1_len != 0)
			return (s1_len - 1);
		i = 0;
	}
	return (s1_len);
}

static char	*ft_insert_str(const char *str, int start, int len, char **new_str)
{
	int		i;

	*new_str = (char *)malloc(len + 1);
	if (!(*new_str))
		return (0);
	i = 0;
	if (len == 0)
	{
		(*new_str)[i] = 0;
		return (*new_str);
	}
	while (len > 0)
	{
		(*new_str)[i] = str[start];
		i++;
		start++;
		len--;
	}
	(*new_str)[i] = 0;
	return (*new_str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		new_len;
	int		start_i;
	int		last_i;
	int		s1_len;

	s1_len = ft_strlen(s1);
	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	start_i = ft_find_start(s1, set, s1_len);
	last_i = ft_find_end(s1, set, s1_len);
	if (start_i == 0 && last_i == 0)
		return (ft_strdup(""));
	new_len = (last_i - start_i) + 1;
	str = ft_insert_str(s1, start_i, new_len, &str);
	return (str);
}

// int	main(void)
// {
// 	printf("%s", ft_strtrim("abcdba", "acb"));
// 	return (0);
// }
