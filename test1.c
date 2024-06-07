#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_signal(int sig) {
    printf("Received signal %d\n", sig);
}

int main() {
    pid_t pid;
    int status;

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process: run an infinite loop
        signal(SIGINT, handle_signal);
        signal(SIGQUIT, handle_signal);
        signal(SIGTERM, handle_signal);
        while (1) {
            sleep(1);
        }
    } else {
        // Parent process: wait for child process to terminate
        printf("Child PID: %d\n", pid);
        sleep(5); // Give some time to send signals

        // Send a signal to the child process
        // kill(pid, SIGINT); // Uncomment to send SIGINT (Ctrl-C)
        // kill(pid, SIGQUIT); // Uncomment to send SIGQUIT (Ctrl-\)
        // kill(pid, SIGTERM); // Uncomment to send SIGTERM

        // Wait for the child process to terminate and get the exit status
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFSIGNALED(status)) {
            int signal_number = WTERMSIG(status);
            int exit_status = 128 + signal_number;
            printf("Child terminated by signal %d, exit status %d\n", signal_number, exit_status);
        } else if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Child exited normally with status %d\n", exit_status);
        } else {
            printf("Child did not terminate normally\n");
        }
    }

    return 0;
}
