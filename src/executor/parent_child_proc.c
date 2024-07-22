/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_proc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:12:29 by goldman           #+#    #+#             */
/*   Updated: 2024/07/22 12:56:40 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"


void	perform_dup_and_close(int old_fd, int new_fd, const char *error_msg, t_shell *shell)
{
	if (old_fd != -1)
	{
		if (dup2(old_fd, new_fd) == -1)
		{
			perror(error_msg);
			shell->exit_code = 1;
			exit(shell->exit_code);
		}
		close(old_fd);
	}
}

void	child_proc(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fd[2])
{
	perform_dup_and_close(input_fd, STDIN_FILENO, "dup2 input_fd", shell);
	perform_dup_and_close(pipe_fd[1], STDOUT_FILENO, "dup2 pipe_fd[1]", shell);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	setup_input_redir(cmd->input, shell);
	setup_output_redir(cmd->output, shell);
	if (handle_builtin(cmd, shell) == -1)
		execute_command(cmd, shell->env_list);
	exit(shell->exit_code);
}


void	parent_proc(int *input_fd, int pipe_fd[2])
{
	if (*input_fd != -1)
		close(*input_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*input_fd = pipe_fd[0];
}
