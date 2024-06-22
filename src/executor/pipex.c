#include "../../includes/executor.h"
#include "../../includes/builtins.h"

// Function to free a split array
void ft_free_split(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Find the correct path for the given command
char *find_correct_path(char *cmd, t_env_var *env_list)
{
    char *path_var = NULL;
    t_env_var *current = env_list;
    char **paths;
    char *correct_path;
    int i = 0;

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
        return NULL;
    paths = ft_split(path_var, ':');
    while (paths[i])
    {
        correct_path = create_cmd_path(paths[i], cmd);
        if (access(correct_path, X_OK) == 0)
        {
            ft_free_split(paths);
            return correct_path;
        }
        free(correct_path);
        i++;
    }
    ft_free_split(paths);
    return NULL;
}

// Create a full path for the command
char *create_cmd_path(char *dir, char *cmd)
{
    char *path = ft_strjoin(dir, "/");
    char *full_path = ft_strjoin(path, cmd);
    free(path);
    return full_path;
}

// Setup input redirection
void setup_input_redirection(int input_fd, t_redirection *input)
{
    int fd = -1;
    if (input_fd != -1)
    {
        if (dup2(input_fd, STDIN_FILENO) == -1)
        {
            perror("dup2 input_fd");
            exit(EXIT_FAILURE);
        }
        close(input_fd);
    }
    if (input && input->file)
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

// Setup output redirection
void setup_output_redirection(int output_fd, t_redirection *output)
{
    int fd = -1;
    if (output_fd != -1)
    {
        if (dup2(output_fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 output_fd");
            exit(EXIT_FAILURE);
        }
        close(output_fd);
    }
    if (output && output->file)
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

// Check if a command is a built-in command
int is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 ||
            ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}

// Execute a built-in command
int execute_builtin(t_command *cmd, t_shell *shell, int output_fd)
{
    int saved_stdout = dup(STDOUT_FILENO); // Save the original stdout

    if (output_fd != STDOUT_FILENO)
    {
        if (dup2(output_fd, STDOUT_FILENO) == -1) // Redirect stdout to the specified output_fd
        {
            perror("dup2 output_fd");
            return 1;
        }
    }

    if (ft_strcmp(cmd->argv[0], "echo") == 0)
    {
        ft_echo(cmd->argv, shell->env_list);
    }
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
    {
        shell->exit_code = ft_cd(cmd->argv, &shell->env_list);
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
        shell->exit_code = ft_env(cmd->argv, shell);
    }
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
    {
        ft_exit(cmd->argv);
    }

    if (output_fd != STDOUT_FILENO)
    {
        dup2(saved_stdout, STDOUT_FILENO); // Restore the original stdout
        close(saved_stdout);
    }

    return shell->exit_code;
}

// Execute a command
void execute_command(t_command *cmd, t_shell *shell)
{
    char *executable_path;
    char **envp;
    int env_count = 0;
    t_env_var *current = shell->env_list;
    int i = 0;

    if (is_builtin(cmd->argv[0]))
    {
        shell->exit_code = execute_builtin(cmd, shell, STDOUT_FILENO);
        if (cmd->next == NULL) // If it's the only command
            exit(shell->exit_code);
        return;
    }

    if (ft_strchr(cmd->argv[0], '/') != NULL)
    {
        executable_path = ft_strdup(cmd->argv[0]);
    }
    else
    {
        executable_path = find_correct_path(cmd->argv[0], shell->env_list);
        if (executable_path == NULL)
        {
            char *error_message = ft_strjoin(cmd->argv[0], ": No such file or directory\n");
            write(STDERR_FILENO, error_message, ft_strlen(error_message));
            free(error_message);
            exit(127);
        }
    }

    current = shell->env_list;
    while (current)
    {
        env_count++;
        current = current->next;
    }
    envp = (char **)malloc((env_count + 1) * sizeof(char *));
    current = shell->env_list;
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

// Setup the child process for execution
void setup_child(t_command *cmd, t_shell *shell, int input_fd, int output_fd)
{
    setup_input_redirection(input_fd, cmd->input);
    setup_output_redirection(output_fd, cmd->output);
    execute_command(cmd, shell);
}

// Close file descriptors
void close_fds(int *input_fd, int *pipe_fd)
{
    if (*input_fd != -1)
        close(*input_fd);
    if (pipe_fd[1] != -1)
        close(pipe_fd[1]);
}

// Handle pipes
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

// Fork and setup the child process
void fork_and_setup(int input_fd, int *pipe_fd, t_command *cmd, t_shell *shell)
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
        if (pipe_fd[1] != -1)
        {
            close(pipe_fd[0]);
            if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
            {
                perror("dup2 output_fd");
                exit(EXIT_FAILURE);
            }
            close(pipe_fd[1]);
        }
        if (input_fd != -1)
        {
            if (dup2(input_fd, STDIN_FILENO) == -1)
            {
                perror("dup2 input_fd");
                exit(EXIT_FAILURE);
            }
            close(input_fd);
        }
        setup_child(cmd, shell, input_fd, pipe_fd[1]);
    }
}

// Execute the list of commands
void execute_commands(t_command *commands, t_shell *shell)
{
    int pipe_fd[2];
    int input_fd = -1;
    pid_t pid;
    t_command *cmd = commands;

    while (cmd)
    {
        handle_pipe(pipe_fd, cmd);
        fork_and_setup(input_fd, pipe_fd, cmd, shell);
        if (input_fd != -1)
            close(input_fd);
        input_fd = pipe_fd[0];
        cmd = cmd->next;
    }
    while ((pid = wait(NULL)) > 0)
        ;
}
