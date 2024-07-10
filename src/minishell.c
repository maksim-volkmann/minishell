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

void handle_redirection(t_command *cmd, t_shell *shell) {
    if (cmd->input)
        setup_input_redirection(cmd->input, shell);
    if (cmd->output)
        setup_output_redirection(cmd->output, shell);
}

int is_builtin(char *command) {
    return (ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "exit") == 0 || ft_strcmp(command, "cd") == 0
        || ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "export") == 0 || ft_strcmp(command, "unset") == 0
        || ft_strcmp(command, "env") == 0);
}

void execute_single_command(t_command *cmd, t_shell *shell) {
    int fd;

    if (cmd->argv[0] == NULL) {
        if (cmd->input && cmd->input->file) {
            if (access(cmd->input->file, F_OK) != 0) {
                fprintf(stderr, "minishell: %s: No such file or directory-1\n", cmd->input->file);
                shell->exit_code = 1;
                return;
            }
        }
        if (cmd->output && cmd->output->file) {
            fd = open(cmd->output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                fprintf(stderr, "minishell: %s: No such file or directory-2\n", cmd->output->file);
                shell->exit_code = 1;
                return;
            }
            close(fd);
        }
        return;
    }

    if (cmd->input && cmd->input->file) {
        if (access(cmd->input->file, F_OK) != 0) {
            fprintf(stderr, "minishell: %s: No such file or directory-3\n", cmd->input->file);
            shell->exit_code = 1;
            return;
        }
    }
    if (cmd->output && cmd->output->file) {
        fd = open(cmd->output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            fprintf(stderr, "minishell: %s: No such file or directory-4\n", cmd->output->file);
            shell->exit_code = 1;
            return;
        }
        close(fd);
    }

    if (is_builtin(cmd->argv[0])) {
        handle_builtin(cmd, shell);
    } else {
        exec_start(cmd, shell);
    }
}

int main(int argc, char **argv, char **env) {
    t_shell shell;

    ft_init_shell(&shell, env);

    // ft_terminal_settings(0); // Save original terminal settings
    // configure_terminal_settings();
    // setup_signal_handlers();

    if (argc > 1 || argv[0] == NULL)
        return 0;
    while (1) {
        shell.cmds = NULL;
        shell.tokens = NULL;
        shell.syn_err_present = false;

        if (isatty(fileno(stdin)))
            shell.input = readline("minishell> ");
        else {
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
        if (ft_strcmp(shell.input, "") == 0) {
            free(shell.input);
            continue;
        }
        ft_lexer(shell.input, &shell);
        ft_parser(&shell, &shell.tokens);
        if (shell.cmds && shell.cmds->next == NULL)
            execute_single_command(shell.cmds, &shell);
        else
            exec_start(shell.cmds, &shell);

        free_command(shell.cmds);
        free_token_list(shell.tokens);
        free(shell.input);
        shell.input = NULL;
    }

    free_env_vars(shell.env_list);
    return shell.exit_code;
}
