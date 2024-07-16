/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goldman <goldman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:26:22 by goldman           #+#    #+#             */
/*   Updated: 2024/07/17 00:39:15 by goldman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int	execute_export_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "export") == 0)
	{
		execute_export(cmd->argv, &shell->env_list, shell);
		return (1);
	}
	return (0);
}

int	execute_unset_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
	{
		execute_unset(cmd->argv, &shell->env_list, shell);
		return (1);
	}
	return (0);
}

int	execute_exit_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		shell->exit_code = execute_exit(cmd->argv, shell);
		return (1);
	}
	return (0);
}