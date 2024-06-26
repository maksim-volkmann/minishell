#include "../../includes/executor.h"
#include <unistd.h> // For getcwd and chdir

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

// Function to find the value of an environment variable
char *get_env_value(t_env_var *env_list, const char *key)
{
    t_env_var *current = env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

// Find the correct path for the given command
char *find_correct_path(char *cmd, t_env_var *env_list)
{
    char *path_var = get_env_value(env_list, "PATH");
    char **paths;
    char *correct_path;
    int i = 0;

    if (!path_var)
        return NULL;
    paths = ft_split(path_var, ':');
    i = 0;
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
void setup_input_redirection(t_redirection *input)
{
    int fd;
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
void setup_output_redirection(t_redirection *output)
{
    int fd;
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

// Function to print environment variables
void print_env_vars(t_env_var *env_list)
{
    t_env_var *current = env_list;

    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

// Function to handle the echo command
void execute_echo(char **argv)
{
    int i = 1;
    int newline = 1;

    // Check for multiple -n flags
    while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }

    // Print the arguments
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }

    // Print newline if -n flag is not set
    if (newline)
        printf("\n");
}

// Function to handle the pwd command
void execute_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("getcwd");
        exit(1);
    }
}

// Function to handle the cd command
void execute_cd(char **argv)
{
    if (argv[1] == NULL)
    {
        fprintf(stderr, "cd: missing argument\n");
        exit(1);
    }
    if (chdir(argv[1]) != 0)
    {
        perror("cd");
        exit(1);
    }
}

// Execute a command
void execute_command(t_command *cmd, t_env_var *env_list)
{
    char *executable_path;

    if (ft_strcmp(cmd->argv[0], "env") == 0)
    {
        print_env_vars(env_list);
        exit(0);
    }

    if (ft_strcmp(cmd->argv[0], "echo") == 0)
    {
        execute_echo(cmd->argv);
        exit(0);
    }

    if (ft_strcmp(cmd->argv[0], "pwd") == 0)
    {
        execute_pwd();
        exit(0);
    }

    if (ft_strcmp(cmd->argv[0], "cd") == 0)
    {
        execute_cd(cmd->argv);
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
            fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
            exit(127);
        }
    }

    // Convert t_env_var list to envp array for execve
    int env_count = 0;
    t_env_var *current = env_list;
    while (current)
    {
        env_count++;
        current = current->next;
    }

    char **envp = malloc(sizeof(char *) * (env_count + 1));
    current = env_list;
    for (int i = 0; i < env_count; i++)
    {
        envp[i] = malloc(strlen(current->key) + strlen(current->value) + 2);
        sprintf(envp[i], "%s=%s", current->key, current->value);
        current = current->next;
    }
    envp[env_count] = NULL;

    execve(executable_path, cmd->argv, envp);

    // Free envp array
    for (int i = 0; i < env_count; i++)
    {
        free(envp[i]);
    }
    free(envp);

    perror("execve failed");
    free(executable_path);
    exit(EXIT_FAILURE);
}

// Fork and execute the command with proper redirections
void fork_and_execute(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)  // Child process
    {
        // Setup input redirection from a pipe or file
        if (input_fd != -1)
        {
            if (dup2(input_fd, STDIN_FILENO) == -1)
            {
                perror("dup2 input_fd");
                exit(EXIT_FAILURE);
            }
            close(input_fd);
        }

        // Setup output redirection to a pipe or file
        if (output_fd != -1)
        {
            if (dup2(output_fd, STDOUT_FILENO) == -1)
            {
                perror("dup2 output_fd");
                exit(EXIT_FAILURE);
            }
            close(output_fd);
        }

        // Setup additional input/output redirections if specified in the command
        setup_input_redirection(cmd->input);
        setup_output_redirection(cmd->output);

        // Execute the command
        execute_command(cmd, env_list);
    }
}

// Execute the list of commands with piping
// This function handles the creation of pipes, forking of processes, and execution of commands in a pipeline.
void execute_commands(t_command *commands, t_shell *shell)
{
    int pipe_fd[2];
    int input_fd = -1;
    t_command *cmd = commands;
    pid_t pid;
    int status;

    while (cmd)
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

        fork_and_execute(cmd, shell->env_list, input_fd, pipe_fd[1]);

        if (input_fd != -1)
            close(input_fd);

        if (pipe_fd[1] != -1)
            close(pipe_fd[1]);

        input_fd = pipe_fd[0];
        cmd = cmd->next;
    }

    while ((pid = wait(&status)) > 0)
    {
        if (WIFEXITED(status))
        {
            shell->exit_code = WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            shell->exit_code = WTERMSIG(status) + 128;
        }
    }
}
