/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preperations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:40:26 by goldman           #+#    #+#             */
/*   Updated: 2024/07/23 12:25:46 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

void	wait_for_last_process(pid_t last_pid, t_shell *shell)
{
	int		status;
	pid_t	pid;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = WTERMSIG(status) + 128;
	pid = wait(NULL);
	while (pid > 0)
		pid = wait(NULL);
}

// pid_t	fork_process(t_cmd *cmd,
//			t_shell *shell, int *input_fd, int pipe_fd[2])
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 		child_proc(cmd, shell, *input_fd, pipe_fd);
// 	else
// 		parent_proc(pid, input_fd, pipe_fd);
// 	return (pid);
// }

pid_t	fork_process(t_cmd *cmd, t_shell *shell, int *input_fd, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_proc(cmd, shell, *input_fd, pipe_fd);
	else
		parent_proc(input_fd, pipe_fd);
	return (pid);
}

int	create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->next != NULL)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	return (0);
}

void	check_input_file(t_cmd *cmd, t_shell *shell)
{
	int	fd;

	if (cmd->input && cmd->input->file)
	{
		fd = open(cmd->input->file, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->input->file);
			shell->exit_code = 1;
			cmd = cmd->next;
			return ;
		}
		close(fd);
	}
}

void	exec_start(t_cmd *commands, t_shell *shell)
{
	int			pipe_fd[2];
	int			input_fd;
	t_cmd		*cmd;
	pid_t		last_pid;

	input_fd = -1;
	cmd = commands;
	while (cmd)
	{
		check_input_file(cmd, shell);
		create_pipe_if_needed(cmd, pipe_fd);
		last_pid = fork_process(cmd, shell, &input_fd, pipe_fd);
		cmd = cmd->next;
	}
	if (input_fd != -1)
		close(input_fd);
	wait_for_last_process(last_pid, shell);
}
