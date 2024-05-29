#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_command(char *cmd[], char **env) {
    execve(cmd[0], cmd, env);
    perror("execve failed");
    exit(EXIT_FAILURE);
}

void setup_child(int input_fd, int output_fd, char *cmd[], char **env) {
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
    execute_command(cmd, env);
}

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)), char **env) {
    int num_commands = 4;
    int pipe_fds[num_commands - 1][2];
    pid_t pids[num_commands];
    int i = 0;

    char *commands[][4] = {
		{"/bin/sleep", "5", NULL},
        {"/bin/ls", "-l", NULL},
        {"/usr/bin/grep", "2023", NULL},
        {"/usr/bin/wc", "-l", NULL},
    };

    // Create pipes
    while (i < num_commands - 1) {
        if (pipe(pipe_fds[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Fork child processes
    i = 0;
    while (i < num_commands) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {
            // Setup redirections
            if (i == 0) {
                // First command: no input redirection
                close(pipe_fds[i][0]); // Close unused read end
                setup_child(-1, pipe_fds[i][1], commands[i], env);
            } else if (i == num_commands - 1) {
                // Last command: no output redirection
                close(pipe_fds[i - 1][1]); // Close unused write end
                setup_child(pipe_fds[i - 1][0], -1, commands[i], env);
            } else {
                // Middle commands: input and output redirection
                close(pipe_fds[i - 1][1]); // Close previous pipe write end
                close(pipe_fds[i][0]); // Close current pipe read end
                setup_child(pipe_fds[i - 1][0], pipe_fds[i][1], commands[i], env);
            }
        } else {
            if (i > 0) {
                close(pipe_fds[i - 1][0]); // Close read end of the previous pipe in parent
                close(pipe_fds[i - 1][1]); // Close write end of the previous pipe in parent
            }
        }
        i++;
    }

    // Parent process closes last pipe ends
    close(pipe_fds[num_commands - 2][0]);
    close(pipe_fds[num_commands - 2][1]);

    // Wait for all children to finish
    i = 0;
    while (i < num_commands) {
        waitpid(pids[i], NULL, 0);
        i++;
    }

    return 0;
}
