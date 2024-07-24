/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:24:58 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/24 12:40:42 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*ft_expand_var(t_shell *shell, char *var)
{
	t_env	*current;
	char	*exp_var;

	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(shell->exit_code));
	if (ft_strcmp(var, " ") == 0)
		return (ft_strdup("$"));
	current = shell->env_list;
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
	return (NULL);
}

char	*ft_extract_var(char *input, int *i)
{
	int			j;
	char		*var;
	const int	var_len = ft_var_len(input, (*i));

	(*i)++;
	if (input[(*i)] == '?')
		return (ft_strdup("?") + ((*i)++, 0));
	if (input[(*i)] == ' ' || input[(*i)] == '\t' || input[(*i)] == '\0')
		return (ft_strdup(" "));
	var = malloc(var_len + 1);
	if (!var)
		return (NULL);
	j = 0;
	while (input[(*i)] && !ft_is_separator_var(input[(*i)]))
		var[j++] = input[(*i)++];
	var[j] = '\0';
	return (var);
}

char	*ft_expand_var_dq(t_shell *shell, char *var)
{
	t_env	*current;
	char	*exp_var;

	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(shell->exit_code));
	if (ft_strcmp(var, " ") == 0 || ft_strcmp(var, "") == 0)
		return (ft_strdup("$"));
	current = shell->env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			exp_var = current->value;
			free(var);
			return (ft_strdup_dq(current->value));
		}
		current = current->next;
	}
	return (NULL);
}
