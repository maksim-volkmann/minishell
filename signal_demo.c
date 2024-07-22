#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

volatile sig_atomic_t interrupted = 0;

// Signal handler for SIGINT
void sigint_handler(int sig) {
    if (sig == SIGINT) {
        interrupted = 1;
        rl_replace_line("", 0); // Clear the current line
        rl_redisplay(); // Redisplay the prompt
        write(STDOUT_FILENO, "\n", 1); // Print a newline to ensure the prompt appears correctly
    }
}

// Function to split input into command and arguments
void parse_input(char *input, char **argv) {
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;
}

// Function to execute a command
void execute_command(char **argv) {
    if (execvp(argv[0], argv) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

int main() {
    pid_t pid;
    struct sigaction sa;

    // Set up the SIGINT handler for the parent process
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART; // Restart interrupted system calls
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if (interrupted) {
            interrupted = 0;
            rl_on_new_line();
            rl_redisplay();
            continue;
        }

        char *input = readline("shell> ");
        if (input == NULL) {
            // Handle end-of-file (Ctrl-D)
            break;
        }

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        if (*input == '\0') {
            // Ignore empty input
            free(input);
            continue;
        }

        // Allocate memory for the command and arguments
        char *argv[100];
        parse_input(input, argv);

        if (strcmp(argv[0], "echo") == 0) {
            // Handle 'echo' command in the parent process
            for (int i = 1; argv[i] != NULL; i++) {
                printf("%s ", argv[i]);
            }
            printf("\n");
        } else {
            // Handle all other commands in the child process
            pid = fork();
            if (pid == -1) {
                perror("fork");
                free(input);
                exit(EXIT_FAILURE);
            }

            if (pid == 0) { // Child process
                // Restore default signal handler in the child process
                signal(SIGINT, SIG_DFL);
                execute_command(argv);
                free(input); // Free memory after execvp
            } else { // Parent process
                int status;
                pid_t result;

                do {
                    result = waitpid(pid, &status, WUNTRACED | WCONTINUED);
                    if (result == -1) {
                        if (errno == EINTR) {
                            continue;
                        }
                        perror("waitpid");
                        break;
                    }
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));

                // Ensure prompt is on a new line after child exits
                if (WIFSIGNALED(status)) {
                    printf("\nshell> ");
                    fflush(stdout);
                }
            }
        }

        free(input);
    }

    return 0;
}
