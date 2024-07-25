/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:18:18 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/25 12:48:59 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	handle_equal_sign(char *arg, t_env **env_list, t_shell *shell)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	printf("seg4\n");
	equal_sign = ft_strchr(arg, '=');
	*equal_sign = '\0';
	key = arg;
	value = equal_sign + 1;
	if (is_valid_var_name(key))
		update_env_var(env_list, key, value);
	else
	{
		*equal_sign = '=';
		print_invalid_identifier(arg, shell);
	}
}

char	*find_plus_equal(const char *str)
{
	return (ft_strnstr(str, "+=", ft_strlen(str)));
}

void	handle_export_arg(char *arg, t_env **env_list, t_shell *shell)
{
	reduce_white_space(arg);

	printf("seg3\n");
	if (find_plus_equal(arg) != NULL)
		handle_plus_equal(arg, env_list, shell);
	else if (ft_strchr(arg, '=') != NULL)
		handle_equal_sign(arg, env_list, shell);
	else
		handle_no_equal_sign(arg, env_list, shell);
	printf("seg5\n");
}

void	print_export_vars(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

// void	execute_export(char **args, t_env **env_list, t_shell *shell)
// {
// 	int	i;

// 	i = 1;
// 	if (args[1] == NULL)
// 		print_export_vars(*env_list);
// 	else
// 	{
// 		while (args[i])
// 		{
// 			handle_export_arg(args[i], env_list, shell);
// 			i++;
// 		}
// 	}
// }

void	execute_export(char **args, t_env **env_list, t_shell *shell)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
		print_export_vars(*env_list);
	else
	{
			while (args[i])
			{
				handle_export_arg(args[i], env_list, shell);
				i++;
			}
		}
		if (shell->exit_code == 0)
			shell->exit_code = 0;
}
