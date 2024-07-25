/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:18:18 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/25 15:03:04 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	handle_plus_equal(char *arg, t_env **env_list, t_shell *shell)
{
	char	*plus_equal_sign;
	char	*key;
	char	*value;

	plus_equal_sign = find_plus_equal(arg);
	*plus_equal_sign = '\0';
	key = arg;
	value = plus_equal_sign + 2;
	if (is_valid_var_name(key))
		find_and_update_var(env_list, key, value);
	else
	{
		*plus_equal_sign = '+';
		print_invalid_identifier(arg, shell);
	}
}

void	find_and_update_var(t_env **env_list, char *key, char *value)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			update_existing_var(current, value);
			return ;
		}
		current = current->next;
	}
	add_env_var(env_list, key, value);
}

void	update_existing_var(t_env *current, char *value)
{
	char	*new_value;

	new_value = ft_strjoin(current->value, value);
	free(current->value);
	current->value = new_value;
}

int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
