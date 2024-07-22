/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:20:45 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/22 12:58:12 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/heredoc.h"

char	*ft_expand_var_dq_hd(t_shell *shell, char *var)
{
	t_env	*current;
	char		*exp_var;

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
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (NULL);
}

char	*ft_expand_var_hd(t_shell *shell, char *var)
{
	t_env	*current;
	char		*exp_var;

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
