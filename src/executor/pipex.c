/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goldman <goldman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:21:16 by goldman           #+#    #+#             */
/*   Updated: 2024/07/15 00:08:00 by goldman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

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

char	*get_env_value(t_env_var *env_list, const char *key)
{
	t_env_var	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
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

char	*find_correct_path(char *cmd, t_env_var *env_list)
{
	char	*path_var;
	char	**paths;
	char	*correct_path;
	int		i;

	path_var = get_env_value(env_list, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
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

void	setup_input_redirection(t_redirection *input, t_shell *shell)
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

void	setup_output_redirection(t_redirection *output, t_shell *shell)
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

void	restore_stdout(int saved_stdout)
{
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

void	setup_redirection(t_command *cmd, int *saved_stdout, t_shell *shell)
{
	if (cmd->output)
	{
		*saved_stdout = dup(STDOUT_FILENO);
		setup_output_redirection(cmd->output, shell);
	}
}

int	execute_echo_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		execute_echo(cmd->argv);
		shell->exit_code = 0;
		return (1);
	}
	return (0);
}

int	execute_pwd_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		execute_pwd();
		shell->exit_code = 0;
		return (1);
	}
	return (0);
}

int	execute_cd_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		shell->exit_code = execute_cd(cmd->argv, &shell->env_list);
		return (1);
	}
	return (0);
}

int	execute_env_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "env") == 0)
	{
		shell->exit_code = execute_env(cmd->argv, shell->env_list);
		return (1);
	}
	return (0);
}

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

int	execute_specific_builtin(t_command *cmd, t_shell *shell)
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

int	handle_builtin(t_command *cmd, t_shell *shell)
{
	int	saved_stdout;
	int	result;

	saved_stdout = -1;
	setup_redirection(cmd, &saved_stdout, shell);
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

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	count_env_vars(t_env_var *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

char	*create_env_var_string(const char *key, const char *value)
{
	char	*env_var;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	env_var = malloc(key_len + value_len + 2);
	if (!env_var)
		return (NULL);
	ft_strcpy(env_var, key);
	env_var[key_len] = '=';
	ft_strcpy(env_var + key_len + 1, value);
	return (env_var);
}

void	free_envp_on_error(char **envp, int i)
{
	while (i > 0)
		free(envp[--i]);
	free(envp);
}

char	**prepare_envp(t_env_var *env_list)
{
	char		**envp;
	int			env_count;
	int			i;
	t_env_var	*current;

	env_count = count_env_vars(env_list);
	envp = malloc(sizeof(char *) * (env_count + 1));
	if (!envp)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		envp[i] = create_env_var_string(current->key, current->value);
		if (!envp[i])
		{
			free_envp_on_error(envp, i);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp[env_count] = NULL;
	return (envp);
}

char	*get_executable_path(char *cmd, t_env_var *env_list)
{
	char	*executable_path;

	if (ft_strchr(cmd, '/') != NULL)
		executable_path = ft_strdup(cmd);
	else
	{
		executable_path = find_correct_path(cmd, env_list);
		if (executable_path == NULL)
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			exit(127);
		}
	}
	return (executable_path);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	execute_command(t_command *cmd, t_env_var *env_list)
{
	char	*executable_path;
	char	**envp;

	executable_path = get_executable_path(cmd->argv[0], env_list);
	envp = prepare_envp(env_list);
	execve(executable_path, cmd->argv, envp);
	free_envp(envp);
	perror("execve failed");
	free(executable_path);
	exit(EXIT_FAILURE);
}

void	handle_error(const char *msg, t_shell *shell)
{
	perror(msg);
	shell->exit_code = 1;
	exit(shell->exit_code);
}

void	perform_redirection(int old_fd, int new_fd, const char *msg, t_shell *shell)
{
	if (old_fd != -1)
	{
		if (dup2(old_fd, new_fd) == -1)
			handle_error(msg, shell);
		close(old_fd);
	}
}

void	child_process(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd, t_shell *shell)
{
	perform_redirection(input_fd, STDIN_FILENO, "dup2 input_fd", shell);
	perform_redirection(output_fd, STDOUT_FILENO, "dup2 output_fd", shell);
	setup_input_redirection(cmd->input, shell);
	setup_output_redirection(cmd->output, shell);
	execute_command(cmd, env_list);
	exit(shell->exit_code);
}

void	parent_process(pid_t pid, int input_fd, int output_fd, t_shell *shell)
{
	int	status;

	if (input_fd != -1)
		close(input_fd);
	if (output_fd != -1)
		close(output_fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = WTERMSIG(status) + 128;
}

void	fork_and_execute(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("fork", shell);
	else if (pid == 0)
		child_process(cmd, env_list, input_fd, output_fd, shell);
	else
		parent_process(pid, input_fd, output_fd, shell);
}

void	check_input_file(t_command *cmd, t_shell *shell)
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

int	create_pipe_if_needed(t_command *cmd, int pipe_fd[2])
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

void	handle_child_process(t_command *cmd, t_shell *shell, int input_fd, int pipe_fd[2])
{
	perform_dup_and_close(input_fd, STDIN_FILENO, "dup2 input_fd", shell);
	perform_dup_and_close(pipe_fd[1], STDOUT_FILENO, "dup2 pipe_fd[1]", shell);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	setup_input_redirection(cmd->input, shell);
	setup_output_redirection(cmd->output, shell);
	if (handle_builtin(cmd, shell) == -1)
		execute_command(cmd, shell->env_list);
	exit(shell->exit_code);
}

void	handle_parent_process(pid_t last_pid, int *input_fd, int pipe_fd[2])
{
	if (*input_fd != -1)
		close(*input_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*input_fd = pipe_fd[0];
}

void	wait_for_last_process(pid_t last_pid, t_shell *shell)
{
	int		status;
	pid_t	pid;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = WTERMSIG(status) + 128;
	while ((pid = wait(NULL)) > 0)
		;
}

void	exec_start(t_command *commands, t_shell *shell)
{
	int			pipe_fd[2];
	int			input_fd;
	t_command	*cmd;
	pid_t		last_pid;

	input_fd = -1;
	cmd = commands;
	while (cmd)
	{
		check_input_file(cmd, shell);
		create_pipe_if_needed(cmd, pipe_fd);
		last_pid = fork();
		if (last_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (last_pid == 0)
			handle_child_process(cmd, shell, input_fd, pipe_fd);
		else
			handle_parent_process(last_pid, &input_fd, pipe_fd);
		cmd = cmd->next;
	}
	if (input_fd != -1)
		close(input_fd);
	wait_for_last_process(last_pid, shell);
}
