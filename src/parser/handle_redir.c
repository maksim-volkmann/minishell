/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:38:09 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/27 10:18:51 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdbool.h>

void	ft_handle_output(t_token *tokens, t_shell *shell, t_redirection *output)
{
	int	fd;

	if (ft_check_filepath(tokens->next->token) == 0)
	{
		// shell->error_present = true;
		ft_putstr_fd("No such Directory\n", 2);
		return ;
	}
	output->file = tokens->next->token;
	if (tokens->type == GREAT)
	{
		output->type = REDIR_OUTPUT;
		fd = open(output->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	}
	else if (tokens->type == DGREAT)
	{
		output->type = REDIR_APPEND;
		fd = open(output->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	}
	if (fd < 0)
	{
		ft_putstr_fd(output->file, 2);
		ft_putstr_fd(": Error creating file\n", 2);
		shell->error_present = true;
	}
	close(fd);
}

void	ft_handle_input(t_token *tokens, t_shell *shell, t_redirection *input)
{
	if (tokens->type == LESS)
	{
		input->type = REDIR_INPUT;
		input->file = tokens->next->token;
		if (access(input->file, F_OK) != -0)
		{
			ft_putstr_fd("Error with Input files, file does not exist\n", 2);
			shell->error_present = true;
			return ;
		}
	}
	else if (tokens->type == DLESS)
	{
		input->type = REDIR_HEREDOC;
		input->file = ft_heredoc(tokens->next->token, shell);
	}
}

void	ft_handle_redir(t_token *tokens, t_shell *shell, t_redirection *input, t_redirection *output)
{
	if (tokens->next == NULL)
	{
		printf("Non existing file out or in file\n");
		shell->error_present = true;
		return ;
	}
	if (tokens->next->type == PIPE)
	{
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
