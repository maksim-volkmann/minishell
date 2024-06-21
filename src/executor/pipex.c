#include "../../includes/executor.h"
#include "../../includes/builtins.h"

void ft_free_split(char **arr)
{
    int i;

    i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char *find_correct_path(char *cmd, t_env_var *env_list)
{
    char *path_var;
    t_env_var *current;
    char **paths;
    char *correct_path;
    int i;

    path_var = NULL;
    current = env_list;
    while (current)
    {
        if (ft_strcmp(current->key, "PATH") == 0)
        {
            path_var = current->value;
            break;
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

char *create_cmd_path(char *dir, char *cmd)
{
    char *path;
    char *full_path;

    path = ft_strjoin(dir, "/");
    full_path = ft_strjoin(path, cmd);
    free(path);
    return (full_path);
}

void setup_input_redirection(int input_fd, t_redirection *input)
{
    int fd;

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

void setup_output_redirection(int output_fd, t_redirection *output)
{
    int fd;

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

int is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0)
    {
        return 1;
    }
    return 0;
}

void execute_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		ft_echo(cmd->argv, shell->env_list);
	}
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		ft_cd(cmd->argv, &shell->env_list, shell);
	}
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
	{
		ft_export(cmd->argv, &shell->env_list);
	}
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		ft_pwd();
	}
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
	{
		ft_unset(cmd->argv, &shell->env_list);
	}
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
	{
		print_env_vars(shell->env_list);
	}
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		ft_exit(cmd->argv);
	}
}



void execute_command(t_command *cmd, t_env_var *env_list)
{
    char *executable_path;
    char **envp;
    int env_count;
    t_env_var *current;
    int i;

    if (is_builtin(cmd->argv[0]))
    {
        execute_builtin(cmd, &env_list);
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
			//TODO: NEED TO COMPARE TO REAL BASH (command should go first).
            // fprintf(stderr, "command not found: %s\n", cmd->argv[0]);
			// printf("%s: No such file or directory\n", cmd->argv[0]);
			char *error_message = ft_strjoin(cmd->argv[0], ": No such file or directory\n");
			write(STDERR_FILENO, error_message, ft_strlen(error_message));
			free(error_message);
            exit(127);
        }
    }

    env_count = 0;
    current = env_list;
    while (current)
    {
        env_count++;
        current = current->next;
    }
    envp = (char **)malloc((env_count + 1) * sizeof(char *));
    current = env_list;
    i = 0;
    while (current)
    {
        envp[i] = ft_strjoin(current->key, "=");
        envp[i] = ft_strjoin(envp[i], current->value);
        current = current->next;
        i++;
    }
    envp[i] = NULL;

    execve(executable_path, cmd->argv, envp);
    perror("execve failed");
    free(executable_path);
    ft_free_split(envp);
    exit(EXIT_FAILURE);
}

void setup_child(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd)
{
    setup_input_redirection(input_fd, cmd->input);
    setup_output_redirection(output_fd, cmd->output);
    execute_command(cmd, env_list);
}

void close_fds(int *input_fd, int *pipe_fd)
{
    if (*input_fd != -1)
        close(*input_fd);
    if (pipe_fd[1] != -1)
        close(pipe_fd[1]);
}

void handle_pipe(int *pipe_fd, t_command *cmd)
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

void fork_and_setup(int input_fd, int *pipe_fd, t_command *cmd, t_env_var *env_list)
{
    pid_t pid;

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

void execute_commands(t_command *commands, t_env_var *env_list)
{
    int pipe_fd[2];
    int input_fd;
    pid_t pid;
    t_command *cmd;

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
