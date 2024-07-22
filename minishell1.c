#include "../includes/executor.h"
#include "../includes/builtins.h"
#include "../includes/parser.h"
#include "../includes/lexer.h"
#include "../includes/minishell.h"
#include "../includes/redirections.h"
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

// volatile int g_exit_status = 0;

// // Function to save and restore terminal settings using a static variable
// void ft_terminal_settings(int mode) {
//     static struct termios original_attributes;

//     if (mode == 0) {
//         // Save current terminal settings
//         tcgetattr(STDIN_FILENO, &original_attributes);
//     } else {
//         // Restore original terminal settings
//         tcsetattr(STDIN_FILENO, TCSANOW, &original_attributes);
//     }
// }

// // Function to configure the terminal settings
// void configure_terminal_settings(void) {
//     struct termios attributes;
//     tcgetattr(STDIN_FILENO, &attributes);
//     attributes.c_lflag &= ~ECHOCTL; // Disable echo for control characters
//     tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
// }

// // Signal handler function
// void signal_handler(int sig) {
//     if (sig == SIGINT) {
//         g_exit_status = 130;
//         write(1, "\n", 1);     // Print a newline
//         rl_replace_line("", 0); // Clear the current input line
//         rl_on_new_line();       // Inform readline that the cursor is on a new line
//         rl_redisplay();         // Redisplay the prompt
//     }
//     // No need to handle SIGQUIT as it will be ignored
// }

// // Function to set up signal handlers
// void setup_signal_handlers(void) {
//     struct sigaction sa;

//     sa.sa_handler = signal_handler;
//     sa.sa_flags = SA_RESTART;  // Restart interrupted system calls
//     sigemptyset(&sa.sa_mask);

//     sigaction(SIGINT, &sa, NULL);

//     // Setup to ignore SIGQUIT
//     sa.sa_handler = SIG_IGN;
//     sigaction(SIGQUIT, &sa, NULL);
// }




// volatile int g_exit_status = 0;

// // Function to save and restore terminal settings using a static variable
// void ft_terminal_settings(int mode) {
//     static struct termios original_attributes;

//     if (mode == 0) {
//         // Save current terminal settings
//         tcgetattr(STDIN_FILENO, &original_attributes);
//     } else {
//         // Restore original terminal settings
//         tcsetattr(STDIN_FILENO, TCSANOW, &original_attributes);
//     }
// }

// // Function to configure the terminal settings
// void configure_terminal_settings(void) {
//     struct termios attributes;
//     tcgetattr(STDIN_FILENO, &attributes);
//     // attributes.c_lflag &= ~ECHOCTL; // Disable echo for control characters
//     tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
// }

// // Signal handler function for the main shell
// void signal_handler(int sig)
// {
//     if (sig == SIGINT)
//     {
// 		// printf("signal running\n");
//         g_exit_status = 130;
//         write(1, "\n", 1);
//         rl_replace_line("", 0);
//         rl_on_new_line();
//         rl_redisplay();
//     }
// }

// // Function to set up signal handlers for the main shell
// void setup_signal_handlers(void)
// {
//     struct sigaction sa;

//     sa.sa_handler = signal_handler;
//     sa.sa_flags = SA_RESTART;
//     sigemptyset(&sa.sa_mask);

//     sigaction(SIGINT, &sa, NULL);
//     sa.sa_handler = SIG_IGN;
//     sigaction(SIGQUIT, &sa, NULL);
// }

// // Signal handler function for child processes
// void child_signal_handler(int sig)
// {
//     // if (sig == SIGINT)
//     //     write(1, "\n", 1);
// }

// // Function to set up signal handlers for child processes
// // void setup_child_signal_handlers(void)
// // {
// //     struct sigaction sa;

// //     sa.sa_handler = child_signal_handler;
// //     sa.sa_flags = SA_RESTART;
// //     sigemptyset(&sa.sa_mask);

// //     sigaction(SIGINT, &sa, NULL);
// //     sa.sa_handler = SIG_IGN;
// //     sigaction(SIGQUIT, &sa, NULL);
// // }

// // Function to reset signal handlers for the main shell
// void reset_signal_handlers(void) {
//     struct sigaction sa;

//     sa.sa_handler = SIG_DFL;
//     sa.sa_flags = 0;
//     sigemptyset(&sa.sa_mask);

//     sigaction(SIGINT, &sa, NULL);
//     sigaction(SIGQUIT, &sa, NULL);
// }







void handle_sigint(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigquit(int sig)
{
    (void)sig;
    // Do nothing
}
void setup_signal_handlers(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = handle_sigquit;
    sigaction(SIGQUIT, &sa, NULL);

    // Reset SIGTERM to default for child processes to handle correctly
    sa.sa_handler = SIG_DFL;
    sigaction(SIGTERM, &sa, NULL);
}







//TODO: Can I re-use this for every error printing?
void	prnt_err(const char *cmd, const char *msg, int code, t_shell *shell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	shell->exit_code = code;
}

void ft_exit(t_shell *shell) {
    free_env_vars(shell->env_list);
    exit(shell->exit_code);
}

void ft_init_shell(t_shell *shell, char *env[]) {
    shell->env_list = NULL;
    copy_env_vars(shell, env);
    shell->exit_code = 0;
}

int ft_heredoc_check(t_shell *shell) {
    ft_lexer(shell->input, shell);
    if (ft_syntax_checker(shell->tokens) == 1 || ft_syntax_checker_2(shell->tokens) == 1 || shell->syn_err_present == true) {
        fprintf(stderr, "syntax error\n");
        free_token_list(shell->tokens);
        shell->exit_code = 2;
        return 1;
    }
    ft_heredoc_loop(shell);
    free_token_list(shell->tokens);
    shell->tokens = NULL;
    return 0;
}

int ft_manage_input(t_shell *shell) {
    if (!shell->input)
        ft_exit(shell);
    add_history(shell->input);
    shell->input = ft_expander_heredoc(shell->input, shell);
    if (ft_strcmp(shell->input, "") == 0) {
        free(shell->input);
        return 1;
    }
    return 0;
}

// void handle_redirection(t_command *cmd, t_shell *shell)
// {
// 	if (cmd->input)
// 		setup_input_redirection(cmd->input, shell);
// 	if (cmd->output)
// 		setup_output_redirection(cmd->output, shell);
// }






// int main(int argc, char **argv, char **env) {
//     t_shell shell;

//     ft_init_shell(&shell, env);

// ft_terminal_settings(0); // Save original terminal settings
//     configure_terminal_settings();
//     setup_signal_handlers(); // Set up signal handlers for the main shell

//     if (argc > 1 || argv[0] == NULL)
//         return 0;
//     while (1) {
//         shell.cmds = NULL;
//         shell.tokens = NULL;
//         shell.syn_err_present = false;

//         if (isatty(fileno(stdin)))
//             shell.input = readline("minishell> ");
//         else {
//             char *line = get_next_line(fileno(stdin));
//             shell.input = ft_strtrim(line, "\n");
//             free(line);
//         }

//         // if (isatty(fileno(stdin))) {
//         //     printf("DEBUG: Interactive mode, printing prompt\n");
//         //     shell.input = readline("minishell> ");
//         // } else {
//         //     char *line = get_next_line(fileno(stdin));
//         //     shell.input = ft_strtrim(line, "\n");
//         //     free(line);
//         // }

//         if (!shell.input)
//             ft_exit(&shell);

//         add_history(shell.input);
//         if (ft_heredoc_check(&shell) == 1)
//             continue;
//         shell.input = ft_expander(shell.input, &shell);
//         if (ft_strcmp(shell.input, "") == 0) {
//             free(shell.input);
//             continue;
//         }
//         ft_lexer(shell.input, &shell);
//         ft_parser(&shell, &shell.tokens);
// 		if (shell.cmds && shell.cmds->next == NULL)
// 			exec_single(shell.cmds, &shell);
// 		else
// 			exec_start(shell.cmds, &shell);

//         free_command(shell.cmds);
//         free_token_list(shell.tokens);
//         free(shell.input);
//         shell.input = NULL;
//     }

//     free_env_vars(shell.env_list);
// 	reset_signal_handlers(); // Reset signal handlers before exiting
//     return shell.exit_code;
// }



int main(int argc, char **argv, char **env)
{
    t_shell shell;

    ft_init_shell(&shell, env);

    // ft_terminal_settings(0); // Save original terminal settings
    // configure_terminal_settings();
    // setup_signal_handlers(); // Set up signal handlers for the main shell

	ft_terminal_settings(0); // Save original terminal settings
	configure_terminal_settings();
	setup_signal_handlers(); // Set up signal handlers for the main shell


    if (argc > 1 || argv[0] == NULL)
        return 0;

    while (1)
    {
        shell.cmds = NULL;
        shell.tokens = NULL;
        shell.syn_err_present = false;

        if (isatty(fileno(stdin)))
            shell.input = readline("minishell> ");
        else
        {
            char *line = get_next_line(fileno(stdin));
            shell.input = ft_strtrim(line, "\n");
            free(line);
        }

        if (!shell.input)
            ft_exit(&shell);

        add_history(shell.input);
        if (ft_heredoc_check(&shell) == 1)
            continue;
        shell.input = ft_expander(shell.input, &shell);
        if (ft_strcmp(shell.input, "") == 0)
        {
            free(shell.input);
            continue;
        }
        ft_lexer(shell.input, &shell);
        ft_parser(&shell, &shell.tokens);
        if (shell.cmds && shell.cmds->next == NULL)
            exec_single(shell.cmds, &shell);
        else
            exec_start(shell.cmds, &shell);

        free_command(shell.cmds);
        free_token_list(shell.tokens);
        free(shell.input);
        shell.input = NULL;
    }

    free_env_vars(shell.env_list);
	reset_signal_handlers(); // Reset signal handlers before exiting
    return shell.exit_code;
}
