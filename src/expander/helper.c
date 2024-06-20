/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:37:14 by adrherna          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/20 13:19:30 by mvolkman         ###   ########.fr       */
=======
/*   Updated: 2024/06/20 14:51:57 by adrherna         ###   ########.fr       */
>>>>>>> 85dd28afb025d06f02a5e90a427d692cb47ce88a
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

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

char	*ft_extract_var(char *input, int *i)
{
	char		*var;
	int			j;
	const int	var_len = ft_var_len(input, (*i));

	(*i)++;
	if (input[(*i)] == '?')
	{
		var = ft_strdup("?");
		(*i)++;
		return (var);
	}
	var = malloc(var_len + 1);
	j = 0;
	while (input[(*i)] != 0)
	{
		if (ft_is_separator_var(input[(*i)]) != 0)
			break ;
		else
		{
			var[j] = input[(*i)];
			j++;
			(*i)++;
		}
		assert(*i < 40 && j < 40);
	}
	var[j] = '\0';
	return (var);
}

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

char	*ft_expand_var(t_env_var *env, char *var)
{
	t_env_var	*current;
	char		*exp_var;

	if (ft_strcmp(var, "?") == 0)
		return (ft_strdup("0"));
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			exp_var = current->value;
			free(var);
			return (ft_strdup(current->value));
		}

		current = current->next;
	}
	assert(0);
	return (NULL);
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
