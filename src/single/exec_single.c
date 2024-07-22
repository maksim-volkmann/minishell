/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:21:16 by goldman           #+#    #+#             */
/*   Updated: 2024/07/22 12:06:09 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: Should I move this to seperate .h file or keep it in minishell.h?
#include "../includes/minishell.h"
# include <unistd.h>
# include <fcntl.h>
#include "../includes/executor.h"

int	validate_input_no_cmd(t_command *cmd, t_shell *shell)
{
	if (cmd->input && cmd->input->file)
	{
		if (access(cmd->input->file, F_OK) != 0)
			return (file_err(cmd->input->file, shell));
	}
	return (0);
}

int	validate_output_no_cmd(t_command *cmd, t_shell *shell)
{
	int	fd;

	if (cmd->output && cmd->output->file)
	{
		fd = open(cmd->output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (file_err(cmd->output->file, shell));
		close(fd);
	}
	return (0);
}

int	validate_input_file(t_command *cmd, t_shell *shell)
{
	if (cmd->input && cmd->input->file)
	{
		if (access(cmd->input->file, F_OK) != 0)
			return (file_err(cmd->input->file, shell));
	}
	return (0);
}

int	validate_output_file(t_command *cmd, t_shell *shell)
{
	int	fd;

	if (cmd->output && cmd->output->file)
	{
		fd = open(cmd->output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (file_err(cmd->output->file, shell));
		close(fd);
	}
	return (0);
}

void	exec_single(t_command *cmd, t_shell *shell)
{
	if (cmd->argv[0] == NULL)
	{
		if (validate_input_no_cmd(cmd, shell))
			return ;
		if (validate_output_no_cmd(cmd, shell))
			return ;
		return ;
	}
	if (validate_input_file(cmd, shell))
		return ;
	if (validate_output_file(cmd, shell))
		return ;
	if (is_builtin(cmd->argv[0]))
		handle_builtin(cmd, shell);
	else
		exec_start(cmd, shell);
}
