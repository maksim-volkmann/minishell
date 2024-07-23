/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:01:16 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/23 13:01:19 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_exit(t_shell *shell)
{
	free_env_vars(shell->env_list);
	exit(shell->exit_code);
}

void	ft_init_shell(t_shell *shell, char *env[])
{
	shell->env_list = NULL;
	copy_env_vars(shell, env);
	shell->exit_code = 0;
}

void	ft_loop_init(t_shell *shell)
{
	shell->cmds = NULL;
	shell->tokens = NULL;
	shell->syn_err_present = false;
}

void	ft_process_input(t_shell *shell)
{
	char	*line;

	if (isatty(fileno(stdin)))
		shell->input = readline("minishell> ");
	else
	{
		line = get_next_line(fileno(stdin));
		shell->input = ft_strtrim(line, "\n");
		free(line);
	}

	if (!shell->input)
		ft_exit(shell);
	add_history(shell->input);
}

int	ft_expander_and_checker(t_shell *shell)
{
	shell->input = ft_expander(shell->input, shell);
	if (ft_strcmp(shell->input, "") == 0)
	{
		free(shell->input);
		return (1);
	}
	return (0);
}

void	ft_end_loop_free(t_shell *shell)
{
	free_command(shell->cmds);
	free_token_list(shell->tokens);
	free(shell->input);
	shell->input = NULL;
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell	shell;

// 	ft_init_shell(&shell, env);

// 	if (argc > 1 || argv[0] == NULL)
// 		return (0);

// 	while (1)
// 	{
// 		shell.cmds = NULL;
// 		shell.tokens = NULL;
// 		shell.syn_err_present = false;

// 		if (isatty(fileno(stdin)))
// 			shell.input = readline("minishell> ");
// 		else
// 		{
// 			char *line = get_next_line(fileno(stdin));
// 			shell.input = ft_strtrim(line, "\n");
// 			free(line);
// 		}

// 		if (!shell.input)
// 			ft_exit(&shell);

// 		add_history(shell.input);
// 		if (ft_heredoc_check(&shell) == 1)
// 			continue ;
// 		shell.input = ft_expander(shell.input, &shell);
// 		if (ft_strcmp(shell.input, "") == 0)
// 		{
// 			free(shell.input);
// 			continue ;
// 		}
// 		ft_lexer(shell.input, &shell);
// 		ft_parser(&shell, &shell.tokens);
// 		if (shell.cmds && shell.cmds->next == NULL)
// 			exec_single(shell.cmds, &shell);
// 		else
// 			exec_start(shell.cmds, &shell);

// 		free_command(shell.cmds);
// 		free_token_list(shell.tokens);
// 		free(shell.input);
// 		shell.input = NULL;
// 	}

// 	free_env_vars(shell.env_list);
// 	return (shell.exit_code);
// }

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	ft_init_shell(&shell, env);
	if (argc > 1 || argv[0] == NULL)
		return (0);
	while (1)
	{
		ft_loop_init(&shell);
		ft_process_input(&shell);
		if (ft_heredoc_check(&shell) == 1)
			continue ;
		if (ft_expander_and_checker(&shell) == 1)
			continue ;
		ft_lexer(shell.input, &shell);
		ft_parser(&shell, &shell.tokens);
		if (shell.cmds && shell.cmds->next == NULL)
			exec_single(shell.cmds, &shell);
		else
			exec_start(shell.cmds, &shell);
		ft_end_loop_free(&shell);
	}
	free_env_vars(shell.env_list);
	return (shell.exit_code);
}
