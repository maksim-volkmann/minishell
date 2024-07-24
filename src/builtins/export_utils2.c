/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:18:18 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/24 20:30:58 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	update_env_var(t_env **env_list, const char *key, const char *value)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	add_env_var(env_list, key, value);
}

void	copy_word(char **dst, char **src, int *in_word)
{
	if (ft_isspace((unsigned char)**src))
	{
		if (*in_word)
		{
			**dst = ' ';
			(*dst)++;
			*in_word = 0;
		}
	}
	else
	{
		**dst = **src;
		(*dst)++;
		*in_word = 1;
	}
	(*src)++;
}

void	print_invalid_identifier(char *arg, t_shell *shell)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	shell->exit_code = 1;
}

void	handle_no_equal_sign(char *arg, t_env **env_list, t_shell *shell)
{
	if (is_valid_var_name(arg))
		update_env_var(env_list, arg, NULL);
	else
		print_invalid_identifier(arg, shell);
}

void	skip_white_space(char **src)
{
	while (ft_isspace((unsigned char)**src))
		(*src)++;
}
