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

// int ft_heredoc_check(t_shell *shell) {
//     ft_lexer(shell->input, shell);
//     if (ft_syntax_checker(shell->tokens) == 1 || ft_syntax_checker_2(shell->tokens) == 1 || shell->syn_err_present == true) {
//         fprintf(stderr, "syntax error\n");
//         free_token_list(shell->tokens);
//         shell->exit_code = 2;
//         return 1;
//     }
//     ft_heredoc_loop(shell);
//     free_token_list(shell->tokens);
//     shell->tokens = NULL;
//     return 0;
// }

// int ft_manage_input(t_shell *shell) {
//     if (!shell->input)
//         ft_exit(shell);
//     add_history(shell->input);
//     shell->input = ft_expander_heredoc(shell->input, shell);
//     if (ft_strcmp(shell->input, "") == 0) {
//         free(shell->input);
//         return 1;
//     }
//     return 0;
// }



// int	ft_heredoc_check(t_shell *shell)
// {
// 	ft_lexer(shell->input, shell);
// 	if (ft_syntax_checker(shell->tokens) == 1
// 		|| ft_syntax_checker_2(shell->tokens) == 1
// 		||shell->syn_err_present == true)
// 	{
// 		ft_putstr_fd("syntax error\n", 2);
// 		free_token_list(shell->tokens);
// 		shell->exit_code = 2;
// 		return (1);
// 	}
// 	ft_heredoc_loop(shell);
// 	free_token_list(shell->tokens);
// 	shell->tokens = NULL;
// 	return (0);
// }


int main(int argc, char **argv, char **env)
{
	t_shell shell;

	ft_init_shell(&shell, env);

	if (argc > 1 || argv[0] == NULL)
		return (0);

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
			continue ;
		shell.input = ft_expander(shell.input, &shell);
		if (ft_strcmp(shell.input, "") == 0)
		{
			free(shell.input);
			continue ;
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
	return (shell.exit_code);
}
