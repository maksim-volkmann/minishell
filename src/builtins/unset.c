/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:19:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/23 12:19:05 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

// Function to remove an environment variable
// This function removes an environment variable with
// the given key from the environment list

void	remove_env_var(t_env **env_list, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

// Function to handle the unset command
// This function removes environment variables based on the provided arguments
void	execute_unset(char **args, t_env **env_list, t_shell *shell)
{
	int	i;
	int	invalid_identifier;

	i = 1;
	invalid_identifier = 0;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			invalid_identifier = 1;
		}
		else
			remove_env_var(env_list, args[i]);
		i++;
	}
	if (invalid_identifier)
		shell->exit_code = 1;
	else
		shell->exit_code = 0;
}

