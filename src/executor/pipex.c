#include "../../includes/executor.h"

void ft_free_split(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return;
	while (arr[i]) {
		free(arr[i]);
		i++;
	}
	free(arr);
}


// Function to find the correct path for a command
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

// Function to create the full command path
char	*create_cmd_path(char *dir, char *cmd)
{
	char	*path;
	char	*full_path;

	path = ft_strjoin(dir, "/");
	full_path = ft_strjoin(path, cmd);
	free(path);
	return (full_path);
}

// Function to set up input redirection
void	setup_input_redirection(int input_fd, t_redirection *input)
{
	int	fd;

	fd = -1;
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input_fd");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}
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

// Function to set up output redirection
void	setup_output_redirection(int output_fd, t_redirection *output)
{
	int	fd;

	fd = -1;
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output_fd");
			exit(EXIT_FAILURE);
		}
		close(output_fd);
	}
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

// Function to execute the echo command
void	ft_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		printf("\nthis is a test for buildin echo\n");
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

// Check if a command is a built-in command
int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	return (0);
}

// Execute built-in commands
void	execute_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(cmd->argv);
}

// Function to execute a command
void	execute_command(t_command *cmd, t_env_var *env_list)
{
	char	*executable_path;

	if (is_builtin(cmd->argv[0]))
	{
		execute_builtin(cmd);
		exit(0);
	}
	if (ft_strchr(cmd->argv[0], '/') != NULL)
	{
		executable_path = ft_strdup(cmd->argv[0]);
	}
	else
	{
		executable_path = find_correct_path(cmd->argv[0], env_list);
		if (executable_path == NULL)
		{
			fprintf(stderr, "command not found: %s\n", cmd->argv[0]);
			exit(127);
		}
	}
	execve(executable_path, cmd->argv, NULL); // NULL can be replaced with an environment array if needed
	perror("execve failed");
	free(executable_path);
	exit(EXIT_FAILURE);
}

// Function to set up the child process
void	setup_child(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd)
{
	setup_input_redirection(input_fd, cmd->input);
	setup_output_redirection(output_fd, cmd->output);
	execute_command(cmd, env_list);
}

// Function to close file descriptors
void	close_fds(int *input_fd, int *pipe_fd)
{
	if (*input_fd != -1)
		close(*input_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

// Function to handle piping
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

// Function to fork and set up child processes
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
	{
		setup_child(cmd, env_list, input_fd, pipe_fd[1]);
	}
}

// Function to execute commands
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
	while ((pid = wait(NULL)) > 0)
		;
}
