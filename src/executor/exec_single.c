/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:17:47 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/25 18:04:59 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

int	validate_input(t_cmd *cmd, t_shell *shell)
{
	if (cmd->input && cmd->input->file)
	{
		if (access(cmd->input->file, F_OK) != 0)
			return (file_err(cmd->input->file, shell));
	}
	return (0);
}

int	validate_output(t_cmd *cmd, t_shell *shell)
{
	int	fd;

	fd = -1;
	if (cmd->output && cmd->output->file)
	{
		if (cmd->output->type == REDIR_OUTPUT)
			fd = open(cmd->output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->output->type == REDIR_APPEND)
			fd = open(cmd->output->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (file_err(cmd->output->file, shell));
		close(fd);
	}
	return (0);
}

void	exec_single(t_cmd *cmd, t_shell *shell)
{
	if (validate_input(cmd, shell))
		return ;
	if (validate_output(cmd, shell))
		return ;
	if (cmd->argv[0] == NULL)
		return ;
	if (is_builtin(cmd->argv[0]))
		handle_builtin(cmd, shell);
	else
		exec_start(cmd, shell);
}
