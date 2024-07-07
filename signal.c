#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <termios.h>

// Original terminal settings stored globally
struct termios orig_termios;

// Signal handler for SIGINT (cmd + C)
void handle_sigint(int sig) {
    // Print a new prompt on a new line
    printf("\n> ");
    fflush(stdout); // Ensure the prompt is displayed immediately
}

// Restore the original terminal settings
void reset_terminal_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

// Set the terminal to raw mode
void set_raw_mode() {
    struct termios new_termios;

    // Get the terminal settings
    tcgetattr(STDIN_FILENO, &orig_termios);

    // Make a copy of the settings to modify
    new_termios = orig_termios;

    // Disable canonical mode and echo
    new_termios.c_lflag &= ~(ICANON | ECHO);

    // Set the new terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    // Ensure the terminal settings are reset on exit
    atexit(reset_terminal_mode);
}

int main() {
    struct sigaction sa;

    // Set up the SIGINT handler
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // Restart interrupted system calls
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Set terminal to raw mode
    set_raw_mode();

    // Main interactive loop
    char buffer[1024];
    while (1) {
        printf("> ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            // Handle EOF (ctrl-D)
            printf("Exiting...\n");
            break;
        }

        // Remove the newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Check for 'exit' command
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }

        // Print the input back to the user
        printf("You entered: %s\n", buffer);
    }

    return 0;
}
