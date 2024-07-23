/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd_cd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:29:21 by mvolkman           #+#    #+#             */
/*   Updated: 2024/07/22 12:56:40 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int	execute_echo_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		execute_echo(cmd->argv);
		shell->exit_code = 0;
		return (1);
	}
	return (0);
}

int	execute_pwd_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		execute_pwd();
		shell->exit_code = 0;
		return (1);
	}
	return (0);
}

int	execute_cd_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		shell->exit_code = execute_cd(cmd->argv, &shell->env_list);
		return (1);
	}
	return (0);
}

int	execute_env_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "env") == 0)
	{
		shell->exit_code = execute_env(cmd->argv, shell->env_list);
		return (1);
	}
	return (0);
}
