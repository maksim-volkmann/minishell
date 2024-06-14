/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:37:14 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/14 12:40:53 by adrherna         ###   ########.fr       */
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

char	*ft_expand_var(t_env_var *env, char *var)
{
	t_env_var	*current;
	char		*exp_var;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			exp_var = current->value;
			free(var);
			return (exp_var);
		}
		current = current->next;
	}
	free(var);
	return (NULL);
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

char	*ft_extract_var(char *input, int *i)
{
	char		*var;
	int			j;
	const int	var_len = ft_var_len(input, (*i));

	var = malloc(var_len + 1);
	if (!var)
		return (NULL);
	(*i)++;
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
	}
	var[j] = '\0';
	return (var);
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
