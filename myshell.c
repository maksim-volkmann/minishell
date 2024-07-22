#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

volatile sig_atomic_t g_exit_status = 0;
volatile sig_atomic_t g_child_running = 0;

void ft_terminal_settings(int mode) {
    static struct termios original_attributes;

    if (mode == 0) {
        // Save current terminal settings
        tcgetattr(STDIN_FILENO, &original_attributes);
    } else {
        // Restore original terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &original_attributes);
    }
}

void configure_terminal_settings(void) {
    struct termios attributes;
    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= ~ECHOCTL; // Disable echo for control characters
    tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
}

void parent_signal_handler(int sig) {
    if (sig == SIGINT) {
        if (!g_child_running) {
            write(1, "\n", 1);     // Print a newline
            rl_replace_line("", 0); // Clear the current input line
            rl_on_new_line();       // Inform readline that the cursor is on a new line
            rl_redisplay();         // Redisplay the prompt
            g_exit_status = 1;      // Set exit status to 1 for Ctrl+C
        }
    }
}

void child_signal_handler(int sig) {
    if (sig == SIGINT) {
        write(1, "^C\n", 3);       // Print ^C followed by a newline
        _exit(128 + SIGINT);         // Exit with status 128 + SIGINT
    }
}

void setup_signal_handlers(void) {
    struct sigaction sa;

    sa.sa_handler = parent_signal_handler;
    sa.sa_flags = SA_RESTART;  // Restart interrupted system calls
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);

    // Setup to ignore SIGQUIT
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
}

void setup_child_signal_handlers(void) {
    struct sigaction sa;

    sa.sa_handler = child_signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = SIG_DFL; // Default behavior for SIGQUIT
    sigaction(SIGQUIT, &sa, NULL);
}

void sigpipe_handler(int sig) {
    printf("Received SIGPIPE\n");
    exit(EXIT_FAILURE);
}

void run_command(char *cmd) {
    char **args = NULL;
    int argc = 0;
    int arg_capacity = 10;
    char *arg = strtok(cmd, " ");

    args = malloc(arg_capacity * sizeof(char *));
    if (!args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (arg != NULL) {
        if (argc >= arg_capacity) {
            arg_capacity *= 2;
            args = realloc(args, arg_capacity * sizeof(char *));
            if (!args) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        args[argc] = arg;
        argc++;
        arg = strtok(NULL, " ");
    }
    args[argc] = NULL;

    execvp(args[0], args);
    perror("execvp");
    free(args);
    exit(EXIT_FAILURE);
}

void execute_pipeline(char *commands[], int n) {
    int **pipefd = NULL;
    pid_t *pids;
    int i, j;
    int in_fd, out_fd;

    if (n > 1) {
        pipefd = malloc((n - 1) * sizeof(int *));
        for (i = 0; i < n - 1; i++) {
            pipefd[i] = malloc(2 * sizeof(int));
            if (pipe(pipefd[i]) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
    }

    pids = malloc(n * sizeof(pid_t));
    if (pids == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    g_child_running = 1;

    in_fd = STDIN_FILENO;
    i = 0;
    while (i < n) {
        out_fd = (i < n - 1) ? pipefd[i][1] : STDOUT_FILENO;

        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pids[i] == 0) {
            // Child process setup
            printf("Child process setup PID:%d\n", getpid());
            setup_child_signal_handlers(); // Set custom signal handlers for child

            if (in_fd != STDIN_FILENO) {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (out_fd != STDOUT_FILENO) {
                dup2(out_fd, STDOUT_FILENO);
                close(out_fd);
            }

            if (pipefd != NULL) {
                for (j = 0; j < n - 1; j++) {
                    close(pipefd[j][0]);
                    close(pipefd[j][1]);
                }
            }

            run_command(commands[i]);
        }

        if (in_fd != STDIN_FILENO) {
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO) {
            close(out_fd);
        }

        in_fd = (i < n - 1) ? pipefd[i][0] : STDIN_FILENO;
        i++;
    }

    if (pipefd != NULL) {
        for (i = 0; i < n - 1; i++) {
            close(pipefd[i][0]);
            close(pipefd[i][1]);
            free(pipefd[i]);
        }
        free(pipefd);
    }

    i = 0;
    while (i < n) {
        int wstatus;
        waitpid(pids[i], &wstatus, 0);
        if (WIFEXITED(wstatus)) {
            g_exit_status = WEXITSTATUS(wstatus);
        } else if (WIFSIGNALED(wstatus)) {
            g_exit_status = 128 + WTERMSIG(wstatus);
        }
        i++;
    }

    g_child_running = 0;

    free(pids);
}

void parse_and_execute(char *input) {
    char **commands = NULL;
    int n = 0;
    int cmd_capacity = 10;
    char *cmd = strtok(input, "|");

    commands = malloc(cmd_capacity * sizeof(char *));
    if (!commands) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (cmd != NULL) {
        if (n >= cmd_capacity) {
            cmd_capacity *= 2;
            commands = realloc(commands, cmd_capacity * sizeof(char *));
            if (!commands) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        commands[n] = cmd;
        n++;
        cmd = strtok(NULL, "|");
    }

    if (n > 0) {
        execute_pipeline(commands, n);
    }

    free(commands);
}

int main() {
    char *input;

    ft_terminal_settings(0);
    configure_terminal_settings();

    setup_signal_handlers();

    while (1) {
        printf("Parent process running with PID %d\n", getpid());
        input = readline("myshell> ");
        if (input == NULL) {
            printf("\n");
            break;
        }
        if (strlen(input) == 0) {
            free(input);
            continue;
        }
        add_history(input);
        parse_and_execute(input);
        free(input);
    }

    rl_clear_history();
    ft_terminal_settings(1);

    return 0;
}
