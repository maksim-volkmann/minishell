/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:46:09 by goldman           #+#    #+#             */
/*   Updated: 2024/07/22 12:43:52 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/executor.h"
#include "../../includes/minishell.h"

void	setup_input_redir(t_redirection *input, t_shell *shell)
{
	int	fd;

	if (input && input->file)
	{
		fd = open(input->file, O_RDONLY);
		if (fd == -1)
		{
			perror(input->file);
			shell->exit_code = 1;
			exit(shell->exit_code);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input redirection file");
			shell->exit_code = 1;
			exit(shell->exit_code);
		}
		close(fd);
	}
}

void	setup_output_redir(t_redirection *output, t_shell *shell)
{
	int	fd;

	fd = -1;
	if (output && output->file)
	{
		if (output->type == REDIR_OUTPUT)
			fd = open(output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (output->type == REDIR_APPEND)
			fd = open(output->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(output->file);
			shell->exit_code = 1;
			exit(shell->exit_code);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output redirection file");
			shell->exit_code = 1;
			exit(shell->exit_code);
		}
		close(fd);
	}
}
