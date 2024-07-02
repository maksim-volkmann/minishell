
#include "../includes/executor.h"
#include "../includes/builtins.h"
#include "../includes/parser.h"
#include "../includes/lexer.h"
#include <stdio.h>

void	ft_exit(t_shell *shell)
{
	free_env_vars(shell->env_list);
	// free(shell->input);
	exit(shell->exit_code);
}

void	ft_init_shell(t_shell *shell, char *env[])
{
	shell->env_list = NULL;
	copy_env_vars(shell, env);
	shell->exit_code = 0;
}

void	ft_heredoc_check(t_shell *shell)
{
	ft_lexer(shell->input, &shell->tokens);
	ft_heredoc_loop(shell);
	free_token_list(shell->tokens);
	shell->tokens = NULL;
}

int	ft_manage_input(t_shell *shell)
{
	if (!shell->input)
		ft_exit(shell);
	add_history(shell->input);
	ft_heredoc_check(shell);
	shell->input = ft_expander(shell->input, shell);
	if (ft_strcmp(shell->input, "") == 0)
	{
		free(shell->input);
		return (1);
	}
	return (0);
}

int	ft_manage_errors(t_shell *shell)
{
	if (shell->error_present == true)
	{
		free_command(shell->cmds);
		free_token_list(shell->tokens);
		free(shell->input);
		return (1);
	}
	return (0);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_token	*tokens;
// 	t_shell	shell;

// 	ft_init_shell(&shell, env);
// 	while (1)
// 	{
// 		shell.cmds = NULL;
// 		shell.tokens = NULL;
// 		shell.input = readline("minishell> ");
// 		if (ft_manage_input(&shell) == 1)
// 			continue ;
// 		ft_lexer(shell.input, &shell.tokens);
// 		ft_parser(&shell, &shell.tokens);
// 		if (ft_manage_errors(&shell) == 1)
// 			continue ;
// 		else if (shell.cmds->argv[0] && shell.cmds->next == NULL)
// 		{
// 			if (ft_strcmp(shell.cmds->argv[0], "exit") == 0)
// 			{
// 				shell.exit_code = execute_exit(shell.cmds->argv, &shell);
// 			}
// 			if (ft_strcmp(shell.cmds->argv[0], "echo") == 0)
// 				execute_echo(shell.cmds->argv);
// 			else
// 				execute_commands(shell.cmds, &shell);
// 		}
// 		else
// 		{
// 			execute_commands(shell.cmds, &shell);
// 		}
// 		free_command(shell.cmds);
// 		free_token_list(shell.tokens);
// 		free(shell.input);
// 		shell.input = NULL;
// 	}
// 	free_env_vars(shell.env_list);
// 	return (shell.exit_code);
// }

		// print_command_details(shell.cmds);
        // print_token_list(shell.tokens);
		// print_env_vars(shell.env_list);

int main(int argc, char **argv, char **env)
{
	//char	*input;
	t_token	*tokens;
	t_shell	shell;

	// ft_bzero(&shell, sizeof shell);
	ft_init_shell(&shell, env);

	while (1)
	{
		shell.cmds = NULL;
		shell.tokens = NULL;

		if (isatty(fileno(stdin)))
			shell.input = readline("minishell> ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			shell.input = ft_strtrim(line, "\n");
			free(line);
		}

		if (!shell.input)
			ft_exit(&shell);

		add_history(shell.input);
		shell.input = ft_expander(shell.input, &shell);

		if (ft_strcmp(shell.input, "") == 0)
		{
			free(shell.input);
			break ;
		}

		ft_lexer(shell.input, &shell.tokens);
		ft_parser(&shell, &shell.tokens);
		// PRINTING SHELL STRUCT!!!
		// print_command_details(shell.cmds);
		// PRINT ENV VARIABLES
		// print_env_vars(shell.env_list);
		if (shell.error_present == true)
		{
			free_command(shell.cmds);
			free_token_list(shell.tokens);
			free(shell.input);
			continue ;
		}
		else if (shell.cmds && shell.cmds->next == NULL)
		{
				// printf("ping2\n");
			// Check for built-in commands
			if (ft_strcmp(shell.cmds->argv[0], "exit") == 0)
			{
				shell.exit_code = execute_exit(shell.cmds->argv, &shell);
				// printf("ping3\n");
				// free(input);
				// free_command(shell.cmds);
				// free_token_list(tokens);
				// break;
			}
			// char buffer[1025];
			// if (ft_strcmp(shell.cmds->argv[0], "pwd") == 0)
			// 	printf("%s\n", getcwd(buffer, sizeof(buffer)));
			if (ft_strcmp(shell.cmds->argv[0], "echo") == 0)
				execute_echo(shell.cmds->argv);
			else
				execute_commands(shell.cmds, &shell);
			// else if (ft_strcmp(shell.cmds->argv[0], "cd") == 0)
			//  execute_cd(shell.cmds->argv);
			// else if (ft_strcmp(shell.cmds->argv[0], "pwd") == 0)
			//  execute_pwd();
			// else if (ft_strcmp(shell.cmds->argv[0], "export") == 0)
			//  execute_export(shell.cmds->argv, shell.env_list);
			// else if (ft_strcmp(shell.cmds->argv[0], "unset") == 0)
			//  execute_unset(shell.cmds->argv, shell.env_list);
			// else if (ft_strcmp(shell.cmds->argv[0], "env") == 0)
			//  print_env_vars(shell.env_list);
		}
		else
		{
			execute_commands(shell.cmds, &shell);
		}

        free_command(shell.cmds);
        free_token_list(shell.tokens);
        free(shell.input);
		shell.input = NULL;
	}
	free_env_vars(shell.env_list);
	return shell.exit_code;
}

// #define TESTER 1


// TO DO
// no expandir variables que se encuentren adentro de Q, quizas con un flag o algo

// unir tokens que con WORD DQ y Q que esten consecutivos

// checkear >">"


	// print_env_vars(shell.env_list);
// void handle_sigint(int sig)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	handle_sigquit(int sig)
// {

// }




		// print_command(shell.cmds);
// To do

// limpiar argv despues de conseguir input y output files

		// print_cmd_list(cmds);
		// print_linked_list(tokens);

// ver si puedo implementar una history
// ver que es expand

// 3.1.2.3 Double Quotes
// Enclosing characters in double quotes
// (‘"’) preserves the literal value of all characters
//  within the quotes, with the exception of ‘$’, ‘`’, ‘\’

// Tilde Expansion:

// Expands the tilde character (~) to the value of the home directory. For example, ~ expands to /home/username.
// Parameter and Variable Expansion:

// Replaces variables with their values. For example, $HOME expands to /home/username.
// Can also include modifiers, such as ${VAR:-default}, which provides a default value if the variable is unset.
