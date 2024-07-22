/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_buildin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:52:06 by goldman           #+#    #+#             */
/*   Updated: 2024/07/22 12:56:40 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

void	restore_stdout(int saved_stdout)
{
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	execute_specific_builtin(t_cmd *cmd, t_shell *shell)
{
	if (execute_echo_builtin(cmd, shell))
		return (0);
	if (execute_pwd_builtin(cmd, shell))
		return (0);
	if (execute_cd_builtin(cmd, shell))
		return (0);
	if (execute_env_builtin(cmd, shell))
		return (0);
	if (execute_export_builtin(cmd, shell))
		return (0);
	if (execute_unset_builtin(cmd, shell))
		return (0);
	if (execute_exit_builtin(cmd, shell))
		return (0);
	return (-1);
}

int	handle_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdout;
	int	result;

	saved_stdout = -1;
	if (cmd->output)
	{
		saved_stdout = dup(STDOUT_FILENO);
		setup_output_redir(cmd->output, shell);
	}
	if (cmd->argv[0] == NULL)
	{
		restore_stdout(saved_stdout);
		return (0);
	}
	result = execute_specific_builtin(cmd, shell);
	if (result == 0)
	{
		restore_stdout(saved_stdout);
		return (0);
	}
	restore_stdout(saved_stdout);
	return (-1);
}
