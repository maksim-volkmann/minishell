/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:17:44 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/23 14:07:29 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/heredoc.h"
#include "../../includes/redirections.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_heredoc_check(t_shell *shell)
{
	ft_lexer(shell->input, shell);
	if (ft_syntax_checker(shell->tokens) == 1
		|| ft_syntax_checker_2(shell->tokens) == 1
		||shell->syn_err_present == true)
	{
		ft_putstr_fd("syntax error\n", 2);
		free_token_list(shell->tokens);
		shell->exit_code = 2;
		return (1);
	}
	ft_heredoc_loop(shell);
	free_token_list(shell->tokens);
	shell->tokens = NULL;
	return (0);
}

void	initialize_heredoc(t_shell *shell, char ***delimiters, int *del_count)
{
	*delimiters = ft_extract_delimiters(shell->tokens);
	*del_count = ft_count_delimiters(shell->tokens);
	return ;
}

void	process_heredoc(t_shell *shell, char **content,
		char **delimiters, int del_count)
{
	int		i;
	char	*line;

	i = 0;
	*content = ft_strdup("");
	while (del_count != 0)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiters[i]) == 0)
		{
			del_count--;
			i++;
		}
		else if (ft_count_delimiters(shell->tokens) > 1 && i >= del_count - 1)
			*content = ft_heredoc_join(*content, line);
		else if (i >= del_count - 1)
			*content = ft_heredoc_join(*content, line);
	}
}

void	ft_heredoc_loop(t_shell *shell)
{
	char	**delimiters;
	int		del_count;
	char	*content;

	initialize_heredoc(shell, &delimiters, &del_count);
	if (del_count == 0)
	{
		free(delimiters);
		return ;
	}
	process_heredoc(shell, &content, delimiters, del_count);
	ft_open_file("./tmp/heredoc.txt", content, shell);
	ft_free_heredoc(content, delimiters);
}


// int	ft_heredoc_check(t_shell *shell)
// {
// 	pid_t	pid;
// 	int		status;

// 	ft_lexer(shell->input, shell);
// 	if (ft_syntax_checker(shell->tokens) == 1
// 		|| ft_syntax_checker_2(shell->tokens) == 1
// 		|| shell->syn_err_present == true)
// 	{
// 		ft_putstr_fd("syntax error\n", 2);
// 		free_token_list(shell->tokens);
// 		shell->exit_code = 2;
// 		return (1);
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		ft_heredoc_loop(shell);
// 		free_token_list(shell->tokens);
// 		exit(0);
// 	}
// 	else
// 		waitpid(pid, &status, 0);
// 	free_token_list(shell->tokens);
// 	shell->tokens = NULL;
// 	return (0);
// }