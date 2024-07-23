#include "../../includes/signals.h"

// int g_signal = 0;
// struct termios orig_termios;


void ft_configure_terminal(void)
{
    struct termios new_termios;

    // Get current terminal settings and save them in orig_termios
    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;

    // Disable ECHOCTL to prevent displaying ^C
    new_termios.c_lflag &= ~ECHOCTL;

    // Apply new terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

// Custom signal handler for SIGINT (Ctrl+C)
void handle_execution_signal(int signal) {
    // g_signal = 1;
    if (signal == SIGINT)
    {
		;
	}
	    if (signal == SIGQUIT)
    {
		;
	}
}

// Custom signal handler for SIGINT (Ctrl+C) during parsing
void handle_parser_signal(int signal)
{
    if (signal == SIGINT) {
        write(STDIN_FILENO, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

// Function to set up signal handlers for the parser
void setup_parser_signals(void) {
    struct sigaction sa;

    sa.sa_handler = handle_parser_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = SIG_IGN; // Ignore SIGQUIT
    sigaction(SIGQUIT, &sa, NULL);
}

// Function to set up signal handlers for execution
void setup_execution_signals(void) {
    struct sigaction sa;

    sa.sa_handler = handle_execution_signal;
	// printf("sa.sa_handler: %p\n", sa.sa_handler);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = SIG_IGN; // Ignore SIGQUIT
    sigaction(SIGQUIT, &sa, NULL);
}

// Function to restore terminal settings
void ft_restore_terminal(int i) {
    static struct termios original_term_settings;
    if (!i)
        tcgetattr(STDIN_FILENO, &original_term_settings);
    else
        tcsetattr(STDIN_FILENO, TCSANOW, &original_term_settings);
}
