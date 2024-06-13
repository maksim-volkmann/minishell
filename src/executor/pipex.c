#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "../../includes/executor.h"

// void	free_env_vars(t_env_var *env_list)
// {
// 	t_env_var *current;
// 	t_env_var *next;

// 	current = env_list;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->key);
// 		free(current->value);
// 		free(current);
// 		current = next;
// 	}
// }

char	*find_path_var(t_env_var *env_list)
{
	t_env_var	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*create_cmd_path(char *dir, char *cmd)
{
	char	*path;
	char	*full_path;

	path = ft_strjoin(dir, "/");
	full_path = ft_strjoin(path, cmd);
	free(path);
	return (full_path);
}

char	*check_command_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = create_cmd_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*find_correct_path(char *cmd, t_env_var *env_list)
{
	char		*path_var;
	t_env_var	*current;
	char		**paths;
	char		*correct_path;
	int			i;

	path_var = NULL;
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
		{
			path_var = current->value;
			break ;
		}
		current = current->next;
	}
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	correct_path = NULL;
	i = 0;
	while (paths[i])
	{
		correct_path = create_cmd_path(paths[i], cmd);
		if (access(correct_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (correct_path);
		}
		free(correct_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void	execute_command(char *cmd[], t_env_var *env_list)
{
	char	*executable_path;

	if (ft_strchr(cmd[0], '/') != NULL)
		executable_path = ft_strdup(cmd[0]);
	else
	{
		executable_path = find_correct_path(cmd[0], env_list);
		if (executable_path == NULL)
		{
			fprintf(stderr, "command not found: %s\n", cmd[0]);
			exit(EXIT_FAILURE);
		}
	}
	execve(executable_path, cmd, NULL);
	perror("execve failed");
	free(executable_path);
	exit(EXIT_FAILURE);
}

void	handle_input_fd(int input_fd)
{
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input_fd");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}
}

void	handle_output_fd(int output_fd)
{
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output_fd");
			exit(EXIT_FAILURE);
		}
		close(output_fd);
	}
}

void	setup_input_redirection(int input_fd, t_redirection *input)
{
	int	fd;

	fd = -1;
	handle_input_fd(input_fd);
	if (input != NULL && input->file != NULL)
	{
		fd = open(input->file, O_RDONLY);
		if (fd == -1)
		{
			perror("open input redirection file");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input redirection file");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

void	setup_output_redirection(int output_fd, t_redirection *output)
{
	int	fd;

	fd = -1;
	handle_output_fd(output_fd);
	if (output != NULL && output->file != NULL)
	{
		if (output->type == REDIR_OUTPUT)
			fd = open(output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (output->type == REDIR_APPEND)
			fd = open(output->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open output redirection file");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output redirection file");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

void	setup_child(int input_fd, int output_fd, t_command *cmd, t_env_var *env_list)
{
	setup_input_redirection(input_fd, cmd->input);
	setup_output_redirection(output_fd, cmd->output);
	execute_command(cmd->argv, env_list);
}

void	close_fds(int *input_fd, int *pipe_fd)
{
	if (*input_fd != -1)
		close(*input_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

void	handle_pipe(int *pipe_fd, t_command *cmd)
{
	if (cmd->next != NULL)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
}

void	fork_and_setup(int input_fd, int *pipe_fd, t_command *cmd, t_env_var *env_list)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		setup_child(input_fd, pipe_fd[1], cmd, env_list);
}

void	execute_commands(t_command *commands, t_env_var *env_list)
{
	int			pipe_fd[2];
	int			input_fd;
	pid_t		pid;
	t_command	*cmd;

	input_fd = -1;
	cmd = commands;
	while (cmd)
	{
		handle_pipe(pipe_fd, cmd);
		fork_and_setup(input_fd, pipe_fd, cmd, env_list);
		close_fds(&input_fd, pipe_fd);
		input_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	pid = wait(NULL);
	while (pid > 0)
		pid = wait(NULL);
}
