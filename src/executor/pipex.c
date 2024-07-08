#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

// Function to free a split array
// This function frees the memory allocated for an array of strings
void ft_free_split(char **arr) {
    int i = 0;
    if (!arr)
        return;
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Function to find the value of an environment variable
// This function searches for the environment variable with the given key and returns its value
char *get_env_value(t_env_var *env_list, const char *key) {
    t_env_var *current = env_list;
    while (current) {
        if (ft_strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

// Function to create a command path by joining a directory and command name
// This function returns a new string that represents the full path of a command
char *create_cmd_path(char *dir, char *cmd) {
    char *path = ft_strjoin(dir, "/");
    char *full_path = ft_strjoin(path, cmd);
    free(path);
    return full_path;
}

// Function to find the correct path for a given command
// This function searches through the PATH environment variable for the executable command
char *find_correct_path(char *cmd, t_env_var *env_list) {
    char *path_var = get_env_value(env_list, "PATH");
    char **paths;
    char *correct_path;
    int i = 0;

    if (!path_var)
        return NULL;
    paths = ft_split(path_var, ':');
    while (paths[i]) {
        correct_path = create_cmd_path(paths[i], cmd);
        if (access(correct_path, X_OK) == 0) {  // Check if the command is executable
            ft_free_split(paths);
            return correct_path;
        }
        free(correct_path);
        i++;
    }
    ft_free_split(paths);
    return NULL;
}

// Function to setup input redirection
// This function redirects the standard input (STDIN) to the specified file
void setup_input_redirection(t_redirection *input, t_shell *shell) {
    int fd;
    if (input && input->file) {
        fd = open(input->file, O_RDONLY);
        if (fd == -1) {
            perror(input->file);
            shell->exit_code = 1;
            exit(shell->exit_code);
        }
        if (dup2(fd, STDIN_FILENO) == -1) {  // Redirect STDIN to the file descriptor
            perror("dup2 input redirection file");
            shell->exit_code = 1;
            exit(shell->exit_code);
        }
        close(fd);
    }
}

// Function to setup output redirection
// This function redirects the standard output (STDOUT) to the specified file
void setup_output_redirection(t_redirection *output, t_shell *shell) {
    int fd = -1;
    if (output && output->file) {
        if (output->type == REDIR_OUTPUT)
            fd = open(output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (output->type == REDIR_APPEND)
            fd = open(output->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            perror(output->file);
            shell->exit_code = 1;
            exit(shell->exit_code);
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {  // Redirect STDOUT to the file descriptor
            perror("dup2 output redirection file");
            shell->exit_code = 1;
            exit(shell->exit_code);
        }
        close(fd);
    }
}

// Function to handle the echo command
// This function prints the provided arguments to the standard output
void execute_echo(char **argv) {
    int i = 1;
    int newline = 1;

    // Check for -n flag (which indicates no newline at the end)
    while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0) {
        int j = 2;
        while (argv[i][j] == 'n') {
            j++;
        }
        if (argv[i][j] == '\0') {
            newline = 0;
            i++;
        } else {
            break;
        }
    }

    // Print the arguments
    while (argv[i]) {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }

    // Print newline if -n flag is not set
    if (newline)
        printf("\n");
}

// Function to handle the exit command
// This function handles the logic for the exit command, including error checking for numeric arguments
int execute_exit(char **argv, t_shell *shell) {
    int count = 0;
    bool has_sign = false;

    // Count the number of arguments
    while (argv[count])
        count++;
    if (count == 1)
        ft_exit(shell);
    if (strcmp(argv[1], "") == 0) {
        shell->exit_code = 255;
        fprintf(stderr, "exit\nminishell: exit: %s: numeric argument required\n", argv[1]);
        ft_exit(shell);
    }
    int i = 0;
    // Check if the argument is a valid number
    while (argv[1][i]) {
        if ((!ft_isdigit(argv[1][i]) && argv[1][i] != '-' && argv[1][i] != '+') ||
            (has_sign && (argv[1][i] == '-' || argv[1][i] == '+'))) {
            shell->exit_code = 255;
            if (count == 2) {
                fprintf(stderr, "exit\nminishell: exit: %s: numeric argument required\n", argv[1]);
                ft_exit(shell);
            } else {
                fprintf(stderr, "exit\nminishell: exit: too many arguments\n");
                ft_exit(shell);
            }
        }
        if (argv[1][i] == '-' || argv[1][i] == '+') {
            has_sign = true;
        }
        i++;
    }
    if (count == 2) {
        shell->exit_code = ft_atoi(argv[1]);
        ft_exit(shell);
    }
    fprintf(stderr, "exit\nminishell: exit: too many arguments\n");
    shell->exit_code = 1;
    return 1;
}

// Function to handle the pwd command
// This function prints the current working directory
void execute_pwd() {
    char buffer[1024];
    char *cwd;

    cwd = getcwd(buffer, sizeof(buffer));
    if (cwd) {
        ft_putstr_fd(cwd, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
    } else {
        perror("getcwd");
    }
}

// Function to update an environment variable
// This function updates the value of an environment variable or adds it if it doesn't exist
void update_env_var(t_env_var **env_list, const char *key, const char *value) {
    t_env_var *current = *env_list;
    while (current) {
        if (ft_strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    add_env_var(env_list, key, value);
}

// Function to update the PWD and OLDPWD environment variables
// This function updates the current and previous working directories
int update_pwd(t_env_var **env_list, char *old_pwd) {
    char buffer[1024];
    char *new_pwd;

    new_pwd = getcwd(buffer, sizeof(buffer));
    if (!new_pwd) {
        perror("getcwd");
        return 1;
    }

    update_env_var(env_list, "OLDPWD", old_pwd);
    update_env_var(env_list, "PWD", new_pwd);

    return 0;
}

// Function to change the directory to the home directory
// This function changes the current working directory to the user's home directory
int change_to_home(t_env_var **env_list) {
    char *home_dir;

    home_dir = get_env_value(*env_list, "HOME");
    if (!home_dir) {
        ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
        return 1;
    }

    if (chdir(home_dir) != 0) {
        perror("chdir");
        return 1;
    }

    return 0;
}

// Function to handle the cd command
// This function changes the current working directory and updates the PWD and OLDPWD environment variables
int execute_cd(char **args, t_env_var **env_list) {
    char buffer[1024];
    char *old_pwd;
    int status;

    old_pwd = getcwd(buffer, sizeof(buffer));
    if (!old_pwd) {
        perror("getcwd");
        return 1;
    }

    if (!args[1]) {
        if (change_to_home(env_list) != 0)
            return 1;
        status = update_pwd(env_list, old_pwd);
        return status;
    }

    if (chdir(args[1]) != 0) {
        ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        return 1;
    }

    status = update_pwd(env_list, old_pwd);

    return status;
}

// Function to handle the env command
// This function prints the current environment variables
int execute_env(char **args, t_env_var *env_list) {
    if (args[1] != NULL) {
        ft_putstr_fd("env: ", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        return 127;
    } else {
        print_env_vars(env_list);
        return 0;
    }
}

// Function to print exported variables
// This function prints all environment variables in the format used by the export command
void print_export_vars(t_env_var *env_list) {
    t_env_var *current = env_list;
    while (current) {
        printf("declare -x %s", current->key);
        if (current->value) {
            printf("=\"%s\"", current->value);
        }
        printf("\n");
        current = current->next;
    }
}

// Function to reduce white space in a string
// This function trims leading, trailing, and excessive spaces between words in a string
void reduce_white_space(char *str) {
    char *dst = str;
    char *src = str;
    int in_word = 0;

    while (ft_isspace((unsigned char)*src))
        src++;

    while (*src) {
        if (ft_isspace((unsigned char)*src)) {
            if (in_word) {
                *dst++ = ' ';
                in_word = 0;
            }
        } else {
            *dst++ = *src;
            in_word = 1;
        }
        src++;
    }

    if (dst > str && ft_isspace((unsigned char)*(dst - 1)))
        dst--;

    *dst = '\0';
}

// Function to check if a variable name is valid
// This function checks if a given string is a valid variable name in the shell
int is_valid_var_name(const char *name) {
    int i;

    if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
        return 0;

    i = 1;
    while (name[i] != '\0') {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

// Function to find the += operator in a string
// This function searches for the += substring in a given string
char *find_plus_equal(const char *str) {
    return ft_strnstr(str, "+=", ft_strlen(str));
}

// Function to handle the export command
// This function sets or updates environment variables based on the provided arguments
void execute_export(char **args, t_env_var **env_list, t_shell *shell) {
    int i = 1;
    char *key;
    char *value;
    int invalid_identifier = 0;

    if (args[1] == NULL) {
        print_export_vars(*env_list);
        return;
    }

    while (args[i]) {
        char *plus_equal_sign = find_plus_equal(args[i]);

        if (plus_equal_sign != NULL) {
            *plus_equal_sign = '\0';
            key = args[i];
            value = plus_equal_sign + 2;

            if (is_valid_var_name(key)) {
                t_env_var *current = *env_list;
                while (current) {
                    if (ft_strcmp(current->key, key) == 0) {
                        char *new_value = ft_strjoin(current->value, value);
                        free(current->value);
                        current->value = new_value;
                        break;
                    }
                    current = current->next;
                }
                if (current == NULL) {
                    add_env_var(env_list, key, value);
                }
            } else {
                *plus_equal_sign = '+';
                ft_putstr_fd("export: ", STDERR_FILENO);
                ft_putstr_fd(args[i], STDERR_FILENO);
                ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
                invalid_identifier = 1;
            }
        } else {
            char *equal_sign = ft_strchr(args[i], '=');

            if (equal_sign != NULL) {
                *equal_sign = '\0';
                key = args[i];
                value = equal_sign + 1;

                if (is_valid_var_name(key)) {
                    update_env_var(env_list, key, value);
                } else {
                    *equal_sign = '=';
                    ft_putstr_fd("export: ", STDERR_FILENO);
                    ft_putstr_fd(args[i], STDERR_FILENO);
                    ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
                    invalid_identifier = 1;
                }
            } else {
                key = args[i];

                if (is_valid_var_name(key)) {
                    update_env_var(env_list, key, NULL);
                } else {
                    ft_putstr_fd("export: ", STDERR_FILENO);
                    ft_putstr_fd(args[i], STDERR_FILENO);
                    ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
                    invalid_identifier = 1;
                }
            }
        }
        i++;
    }

    if (invalid_identifier)
        shell->exit_code = 1;
    else
        shell->exit_code = 0;
}

// Function to remove an environment variable
// This function removes an environment variable with the given key from the environment list
void remove_env_var(t_env_var **env_list, const char *key) {
    t_env_var *current = *env_list;
    t_env_var *prev = NULL;

    while (current) {
        if (ft_strcmp(current->key, key) == 0) {
            if (prev)
                prev->next = current->next;
            else
                *env_list = current->next;

            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to handle the unset command
// This function removes environment variables based on the provided arguments
void execute_unset(char **args, t_env_var **env_list, t_shell *shell) {
    int i = 1;
    int invalid_identifier = 0;

    while (args[i]) {
        if (!is_valid_var_name(args[i])) {
            ft_putstr_fd("unset: ", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
            invalid_identifier = 1;
        } else {
            remove_env_var(env_list, args[i]);
        }
        i++;
    }

    if (invalid_identifier)
        shell->exit_code = 1;
    else
        shell->exit_code = 0;
}

// Function to handle built-in commands
// This function executes built-in commands and handles their input/output redirections
int handle_builtin(t_command *cmd, t_shell *shell) {
    int saved_stdout = -1;

    if (cmd->output) {
        saved_stdout = dup(STDOUT_FILENO);
        setup_output_redirection(cmd->output, shell);
    }

    if (cmd->argv[0] == NULL) {
        if (cmd->output) {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }
        return 0;
    }

    if (ft_strcmp(cmd->argv[0], "echo") == 0) {
        execute_echo(cmd->argv);
        shell->exit_code = 0;
        if (cmd->output) {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }
        return 0;
    }

    if (ft_strcmp(cmd->argv[0], "pwd") == 0) {
        execute_pwd();
        shell->exit_code = 0;
        if (cmd->output) {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }
        return 0;
    }

    if (ft_strcmp(cmd->argv[0], "cd") == 0) {
        shell->exit_code = execute_cd(cmd->argv, &shell->env_list);
        if (cmd->output) {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }
        return 0;
    }

    if (ft_strcmp(cmd->argv[0], "env") == 0) {
        shell->exit_code = execute_env(cmd->argv, shell->env_list);
        if (cmd->output) {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }
        return 0;
    }

    if (ft_strcmp(cmd->argv[0], "export") == 0) {
        execute_export(cmd->argv, &shell->env_list, shell);
        if (cmd->output) {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }
        return 0;
    }

    if (ft_strcmp(cmd->argv[0], "unset") == 0) {
        execute_unset(cmd->argv, &shell->env_list, shell);
        if (cmd->output) {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }
        return 0;
    }

    if (ft_strcmp(cmd->argv[0], "exit") == 0) {
        shell->exit_code = execute_exit(cmd->argv, shell);
        if (cmd->output)
            close(saved_stdout);
        return 0;
    }

    if (cmd->output) {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
    }

    return -1;
}

// Function to execute a command
// This function finds the correct path for the command and executes it using execve
void execute_command(t_command *cmd, t_env_var *env_list) {
    char *executable_path;

    if (ft_strchr(cmd->argv[0], '/') != NULL) {
        executable_path = ft_strdup(cmd->argv[0]);
    } else {
        executable_path = find_correct_path(cmd->argv[0], env_list);
        if (executable_path == NULL) {
            fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
            exit(127);
        }
    }

    int env_count = 0;
    t_env_var *current = env_list;
    while (current) {
        env_count++;
        current = current->next;
    }

    char **envp = malloc(sizeof(char *) * (env_count + 1));
    current = env_list;
    for (int i = 0; i < env_count; i++) {
        envp[i] = malloc(strlen(current->key) + strlen(current->value) + 2);
        sprintf(envp[i], "%s=%s", current->key, current->value);
        current = current->next;
    }
    envp[env_count] = NULL;

    execve(executable_path, cmd->argv, envp);

    for (int i = 0; i < env_count; i++) {
        free(envp[i]);
    }
    free(envp);

    perror("execve failed");
    free(executable_path);
    exit(EXIT_FAILURE);
}

// Function to fork a process and execute a command
// This function handles forking and executing a command with input/output redirections
void fork_and_execute(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd, t_shell *shell) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        shell->exit_code = 1;
        exit(shell->exit_code);
    } else if (pid == 0) {
        if (input_fd != -1) {
            if (dup2(input_fd, STDIN_FILENO) == -1) {
                perror("dup2 input_fd");
                shell->exit_code = 1;
                exit(shell->exit_code);
            }
            close(input_fd);
        }

        if (output_fd != -1) {
            if (dup2(output_fd, STDOUT_FILENO) == -1) {
                perror("dup2 output_fd");
                shell->exit_code = 1;
                exit(shell->exit_code);
            }
            close(output_fd);
        }

        setup_input_redirection(cmd->input, shell);
        setup_output_redirection(cmd->output, shell);

        execute_command(cmd, env_list);
        exit(shell->exit_code);
    } else {
        if (input_fd != -1) close(input_fd);
        if (output_fd != -1) close(output_fd);
        waitpid(pid, &shell->exit_code, 0);
        if (WIFEXITED(shell->exit_code)) {
            shell->exit_code = WEXITSTATUS(shell->exit_code);
        } else if (WIFSIGNALED(shell->exit_code)) {
            shell->exit_code = WTERMSIG(shell->exit_code) + 128;
        }
    }
}

// Function to execute a pipeline of commands
// This function handles setting up pipes between commands and forking processes to execute them
void exec_start(t_command *commands, t_shell *shell) {
    int pipe_fd[2];
    int input_fd = -1;
    t_command *cmd = commands;
    pid_t last_pid = -1;
    int status;

    while (cmd) {
        if (cmd->input && cmd->input->file) {
            int fd = open(cmd->input->file, O_RDONLY);
            if (fd == -1) {
                perror(cmd->input->file);
                shell->exit_code = 1;
                cmd = cmd->next;
                continue;
            }
            close(fd);
        }

        if (cmd->next != NULL) {
            if (pipe(pipe_fd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        } else {
            pipe_fd[0] = -1;
            pipe_fd[1] = -1;
        }

        last_pid = fork();
        if (last_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (last_pid == 0) {
            if (input_fd != -1) {
                if (dup2(input_fd, STDIN_FILENO) == -1) {
                    perror("dup2 input_fd");
                    shell->exit_code = 1;
                    exit(shell->exit_code);
                }
                close(input_fd);
            }

            if (pipe_fd[1] != -1) {
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
                    perror("dup2 pipe_fd[1]");
                    shell->exit_code = 1;
                    exit(shell->exit_code);
                }
                close(pipe_fd[1]);
            }

            if (pipe_fd[0] != -1) close(pipe_fd[0]);

            setup_input_redirection(cmd->input, shell);
            setup_output_redirection(cmd->output, shell);

            if (handle_builtin(cmd, shell) == -1) {
                execute_command(cmd, shell->env_list);
            }
            exit(shell->exit_code);
        } else {
            if (input_fd != -1) close(input_fd);
            if (pipe_fd[1] != -1) close(pipe_fd[1]);
            input_fd = pipe_fd[0];
        }
        cmd = cmd->next;
    }

    if (input_fd != -1) close(input_fd);

    waitpid(last_pid, &status, 0);
    if (WIFEXITED(status)) {
        shell->exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        shell->exit_code = WTERMSIG(status) + 128;
    }

    while (wait(NULL) > 0) {
    }
}
