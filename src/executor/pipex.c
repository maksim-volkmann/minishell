#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include <unistd.h>
#include <limits.h>
#include <errno.h>

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

char *create_cmd_path(char *dir, char *cmd)
{
    char *path = ft_strjoin(dir, "/");
    char *full_path = ft_strjoin(path, cmd);
    free(path);
    return full_path;
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

    while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }

    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }

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
        return;
    }
    if (chdir(argv[1]) != 0)
    {
        perror("cd");
    }
}

// Function to handle the exit command
int execute_exit(char **argv, t_shell *shell)
{
	int count = 0;
	bool	has_sign = false;

	while (argv[count])
		count++;
	if (count == 1)
		ft_exit(shell);
	if (strcmp(argv[1], "") == 0)
	{
		shell->exit_code = 255;
		fprintf(stderr, "exit\nminishell: exit: %s: numeric argument required\n", argv[1]);
		ft_exit(shell);
	}
	int i = 0;
	while (argv[1][i])
	{

		if ((!ft_isdigit(argv[1][i]) && argv[1][i] != '-' && argv[1][i] != '+')
			|| (has_sign && (argv[1][i] == '-' || argv[1][i] == '+')))
		{
			//first_is_numeric = false;
			shell->exit_code = 255;
			if (count == 2)
			{
				fprintf(stderr, "exit\nminishell: exit: %s: numeric argument required\n", argv[1]);
				ft_exit(shell);
			}
			else
			{
				fprintf(stderr, "exit\nminishell: exit: too many arguments\n");
				ft_exit(shell);
			}
		}
		if (argv[1][i] == '-' || argv[1][i] == '+')
		{
			has_sign = true;
		}
		i++;
	}
	if (count == 2)
	{
		shell->exit_code = ft_atoi(argv[1]);
		ft_exit(shell);
	}
	fprintf(stderr, "exit\nminishell: exit: too many arguments\n");
	shell->exit_code = 1;
	return 1;
}



// Function to handle built-in commands
int handle_builtin(t_command *cmd, t_shell *shell)
{
    if (ft_strcmp(cmd->argv[0], "env") == 0)
    {
        print_env_vars(shell->env_list);
        return 1;
    }

    if (ft_strcmp(cmd->argv[0], "echo") == 0)
    {
        execute_echo(cmd->argv);
        return 1;
    }

    if (ft_strcmp(cmd->argv[0], "pwd") == 0)
    {
        execute_pwd();
        return 1;
    }

    if (ft_strcmp(cmd->argv[0], "cd") == 0)
    {
        execute_cd(cmd->argv);
        return 1;
    }

    if (ft_strcmp(cmd->argv[0], "exit") == 0)
    {
        execute_exit(cmd->argv, shell);
        return 1;
    }

    return 0; // Not a built-in command
}

// Execute a command
void execute_command(t_command *cmd, t_env_var *env_list, t_shell *shell)
{
    char *executable_path;

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
void fork_and_execute(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd, t_shell *shell)
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
        execute_command(cmd, env_list, shell);
    }
    else
    {
        if (input_fd != -1)
            close(input_fd);
        if (output_fd != -1)
            close(output_fd);
    }
}

// Execute the list of commands with piping
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

        if (handle_builtin(cmd, shell))
        {
            cmd = cmd->next;
            continue;
        }

        fork_and_execute(cmd, shell->env_list, input_fd, pipe_fd[1], shell);

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

// Function to free environment variables list
// void free_env_vars(t_env_var *env_list)
// {
//     t_env_var *tmp;

//     while (env_list)
//     {
//         tmp = env_list;
//         env_list = env_list->next;
//         free(tmp->key);
//         free(tmp->value);
//         free(tmp);
//     }
// }

// Function to free the command list
void free_command2(t_command *cmd)
{
    t_command *tmp;

    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        ft_free_split(tmp->argv);
        if (tmp->input)
        {
            free(tmp->input->file);
            free(tmp->input);
        }
        if (tmp->output)
        {
            free(tmp->output->file);
            free(tmp->output);
        }
        free(tmp);
    }
}
