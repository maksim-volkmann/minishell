#include "../../includes/executor.h"

// Free a null-terminated array of strings
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

// Check if a string is a number
int ft_strisnum(const char *str)
{
    int i;

    if (!str || !*str)
        return 0;
    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

// Print the environment variables
void print_env_vars(t_env_var *env_list)
{
    t_env_var *current;

    current = env_list;
    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

// Find the correct path for a command using the PATH environment variable
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

// Create the full command path by concatenating the directory and the command
char *create_cmd_path(char *dir, char *cmd)
{
    char *path;
    char *full_path;

    path = ft_strjoin(dir, "/");
    full_path = ft_strjoin(path, cmd);
    free(path);
    return (full_path);
}

// Set up input redirection
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

// Set up output redirection
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

/* MODIFY ENV VARIABLES IN OUR STRUCT - START*/

// Get the value of an environment variable
char *get_env_value(t_env_var *env_list, const char *key)
{
    t_env_var *current = env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

// Add a new environment variable to the linked list in alphabetical order
void add_env_var(t_env_var **env_list, const char *key, const char *value)
{
    t_env_var *new_var;
    t_env_var *current;
    t_env_var *prev;

    new_var = malloc(sizeof(t_env_var));
    if (!new_var)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_var->key = ft_strdup(key);
    new_var->value = ft_strdup(value);
    new_var->next = NULL;

    if (*env_list == NULL || ft_strcmp((*env_list)->key, key) > 0)
    {
        new_var->next = *env_list;
        *env_list = new_var;
    }
    else
    {
        current = *env_list;
        while (current != NULL && ft_strcmp(current->key, key) < 0)
        {
            prev = current;
            current = current->next;
        }
        prev->next = new_var;
        new_var->next = current;
    }
}

// Update the value of an existing environment variable or add it if it doesn't exist
void update_env_var(t_env_var **env_list, const char *key, const char *value)
{
    t_env_var *current = *env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    add_env_var(env_list, key, value);
}

/* MODIFY ENV VARIABLES IN OUR STRUCT - END*/

// Execute the echo command
void ft_echo(char **args)
{
    int i;
    int newline;

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
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
}

// Execute the cd command
void ft_cd(char **args, t_env_var **env_list)
{
    char *old_pwd;
    char *new_pwd;
    char *home_dir;
    char buffer[1024];

    old_pwd = getcwd(buffer, sizeof(buffer));
    if (!old_pwd)
    {
        perror("getcwd");
        return;
    }
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        home_dir = get_env_value(*env_list, "HOME");
        if (!home_dir)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
        if (chdir(home_dir) != 0)
        {
            perror("chdir");
            return;
        }
    }
    else if (chdir(args[1]) != 0)
    {
        perror("chdir");
        return;
    }
    new_pwd = getcwd(buffer, sizeof(buffer));
    if (!new_pwd)
    {
        perror("getcwd");
        return;
    }
    update_env_var(env_list, "OLDPWD", old_pwd);
    update_env_var(env_list, "PWD", new_pwd);
}

// Execute the export command
void ft_export(char **args, t_env_var **env_list)
{
    int i;
    char *sep;
    char *key;
    char *value;

    if (args[1] == NULL)
    {
        print_env_vars(*env_list);
    }
    else
    {
        for (i = 1; args[i]; i++)
        {
            sep = ft_strchr(args[i], '=');
            if (sep)
            {
                key = ft_substr(args[i], 0, sep - args[i]);
                value = ft_strdup(sep + 1);
                update_env_var(env_list, key, value);
                free(key);
                free(value);
            }
            else
            {
                key = ft_strdup(args[i]);
                if (get_env_value(*env_list, key) == NULL)
                {
                    add_env_var(env_list, key, "");
                }
                free(key);
            }
        }
    }
}

// Execute the pwd command
void ft_pwd()
{
    char buffer[1024];
    char *cwd;

    cwd = getcwd(buffer, sizeof(buffer));
    if (cwd)
    {
        ft_putstr_fd(cwd, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
    else
    {
        perror("getcwd");
    }
}

// Execute the unset command
void ft_unset(char **args, t_env_var **env_list)
{
    t_env_var *current;
    t_env_var *prev;
    int i;

    i = 1;
    while (args[i])
    {
        current = *env_list;
        prev = NULL;
        while (current)
        {
            if (ft_strcmp(current->key, args[i]) == 0)
            {
                if (prev == NULL)
                {
                    *env_list = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                free(current->key);
                free(current->value);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
}

// Execute the exit command
void ft_exit(char **args)
{
    int exit_status;

    exit_status = 0;
    if (args[1] && args[2])
    {
        ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
        exit_status = 1;
    }
    else if (args[1] && !ft_strisnum(args[1]))
    {
        ft_putstr_fd("exit: ", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putendl_fd(": numeric argument required", STDERR_FILENO);
        exit_status = 255;
    }
    else if (args[1])
    {
        exit_status = ft_atoi(args[1]);
    }
    exit(exit_status);
}

// Execute the env command to print the environment variables
void ft_env(t_env_var *env_list)
{
    print_env_vars(env_list);
}

// Check if a command is a built-in command
int is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0)
    {
        return 1;
    }
    return 0;
}

// Execute built-in commands
void execute_builtin(t_command *cmd, t_env_var **env_list)
{
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
    {
        ft_echo(cmd->argv);
    }
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
    {
        ft_cd(cmd->argv, env_list);
    }
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
    {
        ft_export(cmd->argv, env_list);
    }
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
    {
        ft_pwd();
    }
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
    {
        ft_unset(cmd->argv, env_list);
    }
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
    {
        ft_env(*env_list);
    }
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
    {
        ft_exit(cmd->argv);
    }
}

// Execute a command, handling both built-in and external commands
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
            fprintf(stderr, "command not found: %s\n", cmd->argv[0]);
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

// Set up the child process for execution
void setup_child(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd)
{
    setup_input_redirection(input_fd, cmd->input);
    setup_output_redirection(output_fd, cmd->output);
    execute_command(cmd, env_list);
}

// Close file descriptors
void close_fds(int *input_fd, int *pipe_fd)
{
    if (*input_fd != -1)
        close(*input_fd);
    if (pipe_fd[1] != -1)
        close(pipe_fd[1]);
}

// Handle piping between commands
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

// Fork and set up child processes
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

// Execute commands with piping
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
    while ((pid = wait(NULL)) > 0);
}
