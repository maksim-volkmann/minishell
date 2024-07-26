/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:01:16 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/26 11:02:24 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/builtins.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../includes/redirections.h"

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

void	ft_execution(t_shell *shell)
{
	if (shell->cmds && shell->cmds->next == NULL)
		exec_single(shell->cmds, shell);
	else
		exec_start(shell->cmds, shell);
}

void	ft_end_loop(t_shell *shell)
{
	free_command(shell->cmds);
	free_token_list(shell->tokens);
	free(shell->input);
	shell->input = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	ft_init_shell(&shell, env);
	ft_init_signals();
	if (argc != 1 && argv[0] != NULL)
		return (0);
	while (1)
	{
		update_exit_code(&shell);
		ft_loop_init(&shell);
		ft_process_input(&shell);
		if (ft_heredoc_check(&shell) == 1)
			continue ;
		if (ft_expander_and_checker(&shell) == 1)
			continue ;
		ft_lexer(shell.input, &shell);
		ft_parser(&shell, &shell.tokens);
		ft_execution(&shell);
		ft_end_loop(&shell);
		parent_signals();
	}
	free_env_vars(shell.env_list);
	ft_restore_terminal(1);
	return (shell.exit_code);
}
