/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:48:49 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/26 10:20:09 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

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

void	ft_exit(t_shell *shell)
{
	free_env_vars(shell->env_list);
	exit(shell->exit_code);
}

void	update_exit_code(t_shell *shell)
{
	if (g_signal_received == SIGINT)
	{
		shell->exit_code = 1;
		g_signal_received = 0;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
