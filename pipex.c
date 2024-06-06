#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "libft/include/libft.h" // Assuming your libft contains necessary functions


// 0: Success - The command or script executed successfully without errors.
// 1: General error - A catchall for general errors.
// 2: Misuse of shell builtins - The shell encountered a misuse of a shell builtin.
// 126: Command invoked cannot execute - The command was found but could not be executed (e.g., permission problems, or the command is not an executable).
// 127: Command not found - The command was not found.
// 128: Invalid exit argument - The exit command was used with an invalid argument.
// 128+n: Fatal error signal "n" - A command was terminated by signal "n". For example, 130 indicates termination by SIGINT (signal 2), 137 indicates termination by SIGKILL (signal 9), etc.
// 130: Script terminated by Control-C - The script was terminated by Control-C.
// 255: Exit status out of range - Exit statuses should be in the range 0-255.

// int	new_waitpid(int id)
// {
// 	int	status;

// 	waitpid(id, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	else if (WIFSIGNALED(status))
// 		return (128 + WTERMSIG(status));
// 	return (status);
// }


typedef enum e_redir_type {
    REDIR_NONE,
    REDIR_INPUT,
    REDIR_OUTPUT,
    REDIR_APPEND,
    REDIR_HEREDOC
} t_redir_type;

typedef struct s_redirection {
    t_redir_type type;
    char *file;
} t_redirection;

typedef struct s_command {
    char **argv;
    t_redirection *input;
    t_redirection *output;
    struct s_command *next;
} t_command;

//REMOVE THIS
t_redirection *create_redirection(t_redir_type type, char *file) {
    t_redirection *new_redir = (t_redirection *)malloc(sizeof(t_redirection));
    if (!new_redir) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_redir->type = type;
    new_redir->file = strdup(file);
    return new_redir;
}

//REMOVE THIS
char **duplicate_argv(char **argv) {
    int argc = 0;
    while (argv[argc]) {
        argc++;
    }

    char **new_argv = (char **)malloc(sizeof(char *) * (argc + 1));
    if (!new_argv) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < argc; i++) {
        new_argv[i] = strdup(argv[i]);
    }
    new_argv[argc] = NULL;

    return new_argv;
}

//REMOVE THIS
t_command *create_command(char **argv) {
    t_command *new_cmd = (t_command *)malloc(sizeof(t_command));
    if (!new_cmd) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_cmd->argv = duplicate_argv(argv);
    new_cmd->input = NULL;
    new_cmd->output = NULL;
    new_cmd->next = NULL;
    return new_cmd;
}
//?? REMOVE THIS?
void add_command(t_command **head, char **argv) {
    t_command *new_cmd = create_command(argv);
    if (*head == NULL) {
        *head = new_cmd;
    } else {
        t_command *current = *head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_cmd;
    }
}

char *create_cmd_path(char *dir, char *cmd) {
    char *path = ft_strjoin(dir, "/");
    char *full_path = ft_strjoin(path, cmd);
    free(path);
    return full_path;
}

char *check_command_in_paths(char **paths, char *cmd) {
    char *full_path;
    int i = 0;
    while (paths[i]) {
        full_path = create_cmd_path(paths[i], cmd);
        if (access(full_path, X_OK) == 0) {
            return full_path;
        }
        free(full_path);
        i++;
    }
    return NULL;
}

void ft_free_split(char **arr) {
    int i = 0;
    if (!arr) {
        return;
    }
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char *find_correct_path(char *cmd, char **env) {
    char *path_var = NULL;
    char **paths;
    char *correct_path;
    int i = 0;

    while (env[i]) {
        if (ft_strncmp(env[i], "PATH=", 5) == 0) {
            path_var = env[i] + 5;
            break;
        }
        i++;
    }

    if (!path_var) {
        return NULL;
    }

    paths = ft_split(path_var, ':');
    correct_path = check_command_in_paths(paths, cmd);
    ft_free_split(paths);

    return correct_path;
}

void execute_command(char *cmd[], char **env) {
    char *executable_path;

    if (ft_strchr(cmd[0], '/') != NULL) {
        executable_path = ft_strdup(cmd[0]);
    } else {
        executable_path = find_correct_path(cmd[0], env);
        if (executable_path == NULL) {
            fprintf(stderr, "command not found: %s\n", cmd[0]);
            exit(EXIT_FAILURE);
        }
    }
    execve(executable_path, cmd, env);
    perror("execve failed");
    free(executable_path);
    exit(EXIT_FAILURE);
}

void setup_child(int input_fd, int output_fd, char *cmd[], char **env, t_redirection *input, t_redirection *output) {
    if (input_fd != -1) {
        if (dup2(input_fd, STDIN_FILENO) == -1) {
            perror("dup2 input_fd");
            exit(EXIT_FAILURE);
        }
        close(input_fd);
    }

    if (output_fd != -1) {
        if (dup2(output_fd, STDOUT_FILENO) == -1) {
            perror("dup2 output_fd");
            exit(EXIT_FAILURE);
        }
        close(output_fd);
    }

    if (input != NULL) {
        int fd = open(input->file, O_RDONLY);
        if (fd == -1) {
            perror("open input redirection file");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2 input redirection file");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }

    if (output != NULL) {
        int fd = open(output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open output redirection file");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2 output redirection file");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }

    execute_command(cmd, env);
}

// REMOVE THIS
void parse_example(t_command **commands) {
    // t_command *cmd1 = create_command((char *[]) {"cat", NULL});
    // // cmd1->input = create_redirection(REDIR_INPUT, "in.txt");
    // *commands = cmd1;

    // t_command *cmd1 = create_command((char *[]) {"cat", NULL});
    // // cmd1->input = create_redirection(REDIR_INPUT, "in.txt");
    // *commands = cmd1;

	t_command *cmd1 = create_command((char *[]) {"gre", "line", NULL});
	cmd1->output = create_redirection(REDIR_OUTPUT, "out.txt");
	cmd1->input = create_redirection(REDIR_INPUT, "in.txt");
	*commands = cmd1;

    // t_command *cmd2 = create_command((char *[]) {"wc", "-l", NULL});
    // cmd2->output = create_redirection(REDIR_OUTPUT, "out.txt");
    // cmd1->next = cmd2;
}

void execute_commands(t_command *commands, char **env) {
    int pipe_fd[2];
    int input_fd = -1;
    pid_t pid;

    t_command *cmd = commands;
    while (cmd) {
        if (cmd->next != NULL) {
            if (pipe(pipe_fd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        } else {
            pipe_fd[0] = -1;
            pipe_fd[1] = -1;
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            setup_child(input_fd, pipe_fd[1], cmd->argv, env, cmd->input, cmd->output);
        }

        if (input_fd != -1) {
            close(input_fd);
        }
        if (pipe_fd[1] != -1) {
            close(pipe_fd[1]);
        }
        input_fd = pipe_fd[0];

        cmd = cmd->next;
    }

    while ((pid = wait(NULL)) > 0);
}

void free_commands(t_command *commands) {
    t_command *cmd;

    while (commands) {
        cmd = commands;
        commands = commands->next;

        if (cmd->input) {
            free(cmd->input->file);
            free(cmd->input);
        }

        if (cmd->output) {
            free(cmd->output->file);
            free(cmd->output);
        }

        for (int i = 0; cmd->argv[i]; i++) {
            free(cmd->argv[i]);
        }
        free(cmd->argv);
        free(cmd);
    }
}

int main(int argc, char **argv, char **env) {
    (void)argc;
    (void)argv;

    t_command *commands = NULL;

    parse_example(&commands);

    execute_commands(commands, env);

    free_commands(commands);

    return 0;
}
