#include "../../includes/executor.h"

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
char *find_correct_path(char *cmd, char **env)
{
    char *path_var = NULL;
    char **paths;
    char *correct_path;
    int i = 0;

    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            path_var = env[i] + 5;
            break;
        }
        i++;
    }
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

// Execute a command
void execute_command(t_command *cmd, char **env)
{
    char *executable_path;

    if (ft_strchr(cmd->argv[0], '/') != NULL)
    {
        executable_path = ft_strdup(cmd->argv[0]);
    }
    else
    {
        executable_path = find_correct_path(cmd->argv[0], env);
        if (executable_path == NULL)
        {
            fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
            exit(127);
        }
    }

    execve(executable_path, cmd->argv, env);
    perror("execve failed");
    free(executable_path);
    exit(EXIT_FAILURE);
}

// Fork and execute the command with proper redirections
void fork_and_execute(t_command *cmd, char **env, int input_fd, int output_fd)
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
        execute_command(cmd, env);
    }
}

// Execute the list of commands with piping
// This function handles the creation of pipes, forking of processes, and execution of commands in a pipeline.
void execute_commands(t_command *commands, char **env)
{
    int pipe_fd[2];       // Array to hold the file descriptors for the pipe
    int input_fd = -1;    // Initial input is standard input (STDIN)
    t_command *cmd = commands;  // Pointer to the current command

    // Iterate over each command in the linked list
    while (cmd)
    {
        // Check if there is a next command
        // If there is a next command, create a pipe
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
            // No next command, so no need for a pipe
            pipe_fd[0] = -1;
            pipe_fd[1] = -1;
        }

        // Fork and execute the current command
        // The current command's output will be piped to the next command's input
        fork_and_execute(cmd, env, input_fd, pipe_fd[1]);

        // Close the input file descriptor if it is valid
        if (input_fd != -1)
            close(input_fd);

        // Close the write end of the pipe in the parent process
        if (pipe_fd[1] != -1)
            close(pipe_fd[1]);

        // The read end of the pipe becomes the input for the next command
        input_fd = pipe_fd[0];

        // Move to the next command in the list
        cmd = cmd->next;
    }

    // Wait for all child processes to finish
    while (wait(NULL) > 0);
}
