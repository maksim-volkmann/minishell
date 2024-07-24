/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:17:47 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/24 18:54:36 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

int	validate_input_no_cmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->input && cmd->input->file)
	{
		if (access(cmd->input->file, F_OK) != 0)
			return (file_err(cmd->input->file, shell));
	}
	return (0);
}

int	validate_output_no_cmd(t_cmd *cmd, t_shell *shell)
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


//TODO: check this if works after fixing parser.
// int	validate_input_no_cmd(t_cmd *cmd, t_shell *shell)
// {
// 	if (cmd->input && !cmd->input->file)
// 	{
// 		prnt_err("syntax error", "near unexpected token `newline1'", 258, shell);
// 		return (1);
// 	}
// 	return (0);
// }

// int	validate_output_no_cmd(t_cmd *cmd, t_shell *shell)
// {
// 	if (cmd->output && !cmd->output->file)
// 	{
// 		prnt_err("syntax error", "near unexpected token `newline2'", 258, shell);
// 		return (1);
// 	}
// 	return (0);
// }

int	validate_input_file(t_cmd *cmd, t_shell *shell)
{
	if (cmd->input && cmd->input->file)
	{
		if (access(cmd->input->file, F_OK) != 0)
			return (file_err(cmd->input->file, shell));
	}
	return (0);
}

int	validate_output_file(t_cmd *cmd, t_shell *shell)
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
