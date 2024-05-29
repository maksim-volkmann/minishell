#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void execute_command(char *cmd[], char **env) {
    execve(cmd[0], cmd, env); // Use the env parameter correctly here
    perror("execve failed");
    exit(EXIT_FAILURE);
}

void setup_child(int input_fd, int output_fd, char *cmd[], char **env) {
    if (input_fd != -1) {
        dup2(input_fd, STDIN_FILENO); // Redirect stdin to input_fd
        close(input_fd);
    }
    if (output_fd != -1) {
        dup2(output_fd, STDOUT_FILENO); // Redirect stdout to output_fd
        close(output_fd);
    }
    execute_command(cmd, env);
}

int main(int argc, char **argv, char **env) {
    int pipe_fd1[2], pipe_fd2[2];
    pid_t pid1, pid2, pid3;

    // Ensure correct number of arguments
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create first pipe
    if (pipe(pipe_fd1) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child to run "ls -l"
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        close(pipe_fd1[0]); // Close read end of first pipe
        setup_child(-1, pipe_fd1[1], (char *[]){"/bin/ls", "-l", NULL}, env);
    }

    // Create second pipe
    if (pipe(pipe_fd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the second child to run "grep 2023"
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        close(pipe_fd1[1]); // Close write end of first pipe
        close(pipe_fd2[0]); // Close read end of second pipe
        setup_child(pipe_fd1[0], pipe_fd2[1], (char *[]){"/usr/bin/grep", "2023", NULL}, env);
    }

    // Fork the third child to run "wc -l"
    pid3 = fork();
    if (pid3 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid3 == 0) {
        close(pipe_fd1[0]); // Close read end of first pipe
        close(pipe_fd1[1]); // Close write end of first pipe
        close(pipe_fd2[1]); // Close write end of second pipe
        setup_child(pipe_fd2[0], -1, (char *[]){"/usr/bin/wc", "-l", NULL}, env);
    }

    // Parent process closes all pipe ends
    close(pipe_fd1[0]);
    close(pipe_fd1[1]);
    close(pipe_fd2[0]);
    close(pipe_fd2[1]);

    // Wait for all children to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}
