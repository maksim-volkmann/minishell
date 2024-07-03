/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:38:09 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/03 10:33:40 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

void	ft_handle_output(t_token *tokens, t_shell *shell, t_redirection *output)
{
	int	fd;

	// if (ft_check_filepath(tokens->next->token) == 0)
	// {
	// 	shell->exit_code = 1;
	// 	ft_putstr_fd("No such Directory\n", 2);
	// 	return ;
	// }
	output->file = tokens->next->token;
	if (tokens->type == GREAT)
	{
		output->type = REDIR_OUTPUT;
	}
	else if (tokens->type == DGREAT)
	{
		output->type = REDIR_APPEND;
	}
	// if (fd < 0)
	// {
	// 	ft_putstr_fd(output->file, 2);
	// 	ft_putstr_fd(": Error creating file\n", 2);
	// 	shell->error_present = true;
	// }
	close(fd);
}

void	ft_handle_input(t_token *tokens, t_shell *shell, t_redirection *input)
{
	if (tokens->type == LESS)
	{
		input->type = REDIR_INPUT;
		input->file = tokens->next->token;
		// if (access(input->file, F_OK) != -0)
		// {
		// 	fprintf(stderr, "no such file or directory: %s\n", input->file);
		// 	shell->exit_code = 1;
		// 	return ;
		// }
	}
}

void	ft_handle_redir(t_token *tokens, t_shell *shell
		, t_redirection *input, t_redirection *output)
{
	if (tokens->next == NULL)
	{
		printf("Non existing file out or in file\n");
		shell->exit_code = 1;
		shell->error_present = true;
		return ;
	}
	if (tokens->next->type == PIPE)
	{
		shell->exit_code = 1;
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putstr_fd("'|'\n", 2);
		shell->error_present = true;
		return ;
	}
	if (tokens->type == GREAT || tokens->type == DGREAT)
	{
		ft_handle_output(tokens, shell, output);
	}
	if (tokens->type == LESS || tokens->type == DLESS)
	{
		ft_handle_input(tokens, shell, input);
	}
}
