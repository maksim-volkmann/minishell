#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Define the t_command struct for the linked list
typedef struct s_command {
    char **argv; // Pointer to an array of command and arguments
    struct s_command *next; // Pointer to the next command
} t_command;

// Executes a command using execve
void execute_command(char *cmd[], char **env) {
    execve(cmd[0], cmd, env);
    perror("execve failed");
    exit(EXIT_FAILURE);
}

// Sets up redirections for a child process and executes the command
void setup_child(int input_fd, int output_fd, char *cmd[], char **env) {
    // If input_fd is valid, redirect stdin to input_fd
    if (input_fd != -1) {
        if (dup2(input_fd, STDIN_FILENO) == -1) {
            perror("dup2 input_fd");
            exit(EXIT_FAILURE);
        }
        close(input_fd); // Close the duplicated file descriptor
    }

    // If output_fd is valid, redirect stdout to output_fd
    if (output_fd != -1) {
        if (dup2(output_fd, STDOUT_FILENO) == -1) {
            perror("dup2 output_fd");
            exit(EXIT_FAILURE);
        }
        close(output_fd); // Close the duplicated file descriptor
    }

    // Execute the command
    execute_command(cmd, env);
}

// Creates a new command node
t_command *create_command(char **argv) {
    t_command *new_cmd = (t_command *)malloc(sizeof(t_command));
    if (!new_cmd) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Count the number of arguments
    int argc = 0;
    while (argv[argc]) {
        argc++;
    }

    // Allocate memory for the arguments array
    new_cmd->argv = (char **)malloc(sizeof(char *) * (argc + 1));
    if (!new_cmd->argv) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Copy the arguments
    for (int i = 0; i < argc; i++) {
        new_cmd->argv[i] = argv[i];
    }
    new_cmd->argv[argc] = NULL; // Terminate the array with NULL

    new_cmd->next = NULL;
    return new_cmd;
}

// Adds a command to the end of the linked list
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

// Populates the linked list with initial commands
void populate_commands(t_command **head) {
    add_command(head, (char *[]) {"/bin/sleep", "1", NULL});
    add_command(head, (char *[]) {"/bin/ls", "-l", NULL});
    add_command(head, (char *[]) {"/usr/bin/grep", "2023", NULL});
    add_command(head, (char *[]) {"/usr/bin/wc", "-m", NULL});
    add_command(head, (char *[]) {"/usr/bin/wc", "-l", NULL});
}

int main(int argc, char **argv, char **env) {
    (void)argc; // Suppress unused parameter warning
    (void)argv; // Suppress unused parameter warning

    int num_commands = 5; // Number of commands to be executed

    // Array to store file descriptors for pipes
    int pipe_fds[num_commands - 1][2];

    // Array to store process IDs of child processes
    pid_t pids[num_commands];

    // Linked list head for commands
    t_command *commands = NULL;

    // Populate the linked list with commands
    populate_commands(&commands);

    // Counter variable for loops
    int i = 0;

    // Create pipes for inter-process communication
    while (i < num_commands - 1) {
        if (pipe(pipe_fds[i]) == -1) { // Create a pipe and check for errors
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Fork child processes to execute commands
    i = 0;
    t_command *current_cmd = commands;
    while (i < num_commands) {
        pids[i] = fork(); // Fork a new process
        if (pids[i] == -1) { // Check for fork errors
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) { // Child process
            // Setup redirections for the child process
            if (i == 0) {
                // First command: no input redirection
                close(pipe_fds[i][0]); // Close unused read end of the pipe
                setup_child(-1, pipe_fds[i][1], current_cmd->argv, env); // Set up output redirection to the pipe
            } else if (i == num_commands - 1) {
                // Last command: no output redirection
                close(pipe_fds[i - 1][1]); // Close unused write end of the previous pipe
                setup_child(pipe_fds[i - 1][0], -1, current_cmd->argv, env); // Set up input redirection from the previous pipe
            } else {
                // Middle commands: both input and output redirection
                close(pipe_fds[i - 1][1]); // Close previous pipe write end
                close(pipe_fds[i][0]); // Close current pipe read end
                setup_child(pipe_fds[i - 1][0], pipe_fds[i][1], current_cmd->argv, env); // Set up both input and output redirections
            }

            // Close all pipe ends in the child process to avoid hanging
            int j = 0;
            while (j < num_commands - 1) {
                close(pipe_fds[j][0]);
                close(pipe_fds[j][1]);
                j++;
            }
        } else { // Parent process
            if (i > 0) {
                // Close read and write ends of the previous pipe in the parent process
                close(pipe_fds[i - 1][0]);
                close(pipe_fds[i - 1][1]);
            }
        }
        current_cmd = current_cmd->next; // Move to the next command in the list
        i++;
    }

    // Parent process closes all remaining pipe ends
    i = 0;
    while (i < num_commands - 1) {
        close(pipe_fds[i][0]);
        close(pipe_fds[i][1]);
        i++;
    }

    // Wait for all child processes to finish
    i = 0;
    while (i < num_commands) {
        waitpid(pids[i], NULL, 0);
        i++;
    }

    // Free the linked list
    t_command *tmp;
    while (commands) {
        tmp = commands;
        commands = commands->next;
        free(tmp->argv); // Free the argv array
        free(tmp); // Free the command node
    }

    return 0;
}
