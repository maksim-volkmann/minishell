#include "../../includes/signals.h"

// int g_signal = 0;
// struct termios orig_termios;

// Function to configure terminal settings
// void	ft_configure_terminal(void)
// {
// 	struct termios	new_term;

// 	tcgetattr(STDIN_FILENO, &new_term);
// 	new_term.c_lflag &= ~(ECHOCTL);
// 	new_term.c_cc[VQUIT] = _POSIX_VDISABLE;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
// }

// // Custom signal handler for SIGINT (Ctrl+C)
// void	handle_execution_signal(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		// Handle SIGINT during execution
// 	}
// 	if (signal == SIGQUIT)
// 	{
// 		// Handle SIGQUIT during execution
// 	}
// }

// // Custom signal handler for SIGINT (Ctrl+C) during parsing
// void	handle_parser_signal(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		write(STDIN_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// // Function to set up signal handlers for the parser
// void	setup_parser_signals(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = handle_parser_signal;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa, NULL);

// 	sa.sa_handler = SIG_IGN; // Ignore SIGQUIT
// 	sigaction(SIGQUIT, &sa, NULL);
// }

// // Function to set up signal handlers for execution
// void	setup_execution_signals(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = handle_execution_signal;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa, NULL);

// 	sa.sa_handler = SIG_IGN; // Ignore SIGQUIT
// 	sigaction(SIGQUIT, &sa, NULL);
// }

// // Function to restore terminal settings
// void ft_restore_terminal(int i) {
//     static struct termios original_term_settings;
//     if (!i)
//         tcgetattr(STDIN_FILENO, &original_term_settings);
//     else
//         tcsetattr(STDIN_FILENO, TCSANOW, &original_term_settings);
// }


#include "signals.h"
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t g_signal_received = 0;

// Function to configure terminal settings
void	ft_configure_terminal(void)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ECHOCTL);
	new_term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

// Custom signal handler for SIGINT (Ctrl+C)
void	handle_execution_signal(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
	{
		g_signal_received = signal; // Update the global variable first
	}
}

// Custom signal handler for SIGINT (Ctrl+C) during parsing
void	handle_parser_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_signal_received = signal; // Update the global variable first
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		printf("g_signal_received %d \n", g_signal_received);
	}
}

// Function to set up signal handlers for the parser
void	setup_parser_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_parser_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN; // Ignore SIGQUIT
	sigaction(SIGQUIT, &sa, NULL);
}

// Function to set up signal handlers for execution
void	setup_execution_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_execution_signal;
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
