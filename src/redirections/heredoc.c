/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:17:44 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/22 16:13:48 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/heredoc.h"
#include "../../includes/redirections.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>

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

char	*initialize_heredoc(t_shell *shell, char ***delimiters, int *del_count)
{
	*delimiters = ft_extract_delimiters(shell->tokens);
	*del_count = ft_count_delimiters(shell->tokens);
	return (ft_strdup(""));
}

void	process_heredoc(t_shell *shell, char **content,
		char **delimiters, int del_count)
{
	int		i;
	char	*line;

	i = 0;
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

	content = initialize_heredoc(shell, &delimiters, &del_count);
	if (del_count == 0)
		return ;
	process_heredoc(shell, &content, delimiters, del_count);
	ft_open_file("./tmp/heredoc.txt", content, shell);
	ft_free_heredoc(content, delimiters);
}

// void	process_line(char **content, char *line,
	// char **delimiters, int *del_count, int *i)
// {
// 	if (ft_strcmp(line, delimiters[*i]) == 0)
// 	{
// 		(*del_count)--;
// 		(*i)++;
// 	}
// 	else if (*del_count > 1 && *i >= *del_count - 1)
// 		*content = ft_heredoc_join(*content, line);
// 	else if (*i >= *del_count - 1)
// 		*content = ft_heredoc_join(*content, line);
// }

// void	ft_heredoc_loop(t_shell *shell)
// {
// 	char	**delimiters;
// 	int		del_count;
// 	char	*content;
// 	int		i;
// 	char	*line;

// 	delimiters = ft_extract_delimiters(shell->tokens);
// 	del_count = ft_count_delimiters(shell->tokens);
// 	content = ft_strdup("");
// 	i = 0;
// 	if (del_count == 0)
// 		return ;
// 	while (del_count != 0)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		process_line(&content, line, delimiters, &del_count, &i);
// 	}
// 	ft_open_file("./tmp/heredoc.txt", content, shell);
// 	ft_free_heredoc(content, delimiters);
// }

// void	ft_heredoc_loop(t_shell *shell)
// {
// 	char	**delimiters;
// 	int		del_count;
// 	char	*content;
// 	char	*line;
// 	int		i;

// 	delimiters = ft_extract_delimiters(shell->tokens);
// 	del_count = ft_count_delimiters(shell->tokens);
// 	content = ft_strdup("");
// 	i = 0;

// 	if (ft_count_delimiters(shell->tokens) == 0)
// 		return ;
// 	while (del_count != 0)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (ft_strcmp(line, delimiters[i]) == 0)
// 		{
// 			del_count -= 1;
// 			i++;
// 		}
// 		else if (ft_count_delimiters(shell->tokens) > 1 && i >= del_count - 1)
// 			content = ft_heredoc_join(content, line);
// 		else if (i >= del_count - 1)
// 			content = ft_heredoc_join(content, line);
// 	}
// 	ft_open_file("./tmp/heredoc.txt", content, shell);
// 	ft_free_heredoc(content, delimiters);
// }
