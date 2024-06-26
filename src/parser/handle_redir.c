/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:38:09 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/26 11:10:16 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdbool.h>

void	ft_handle_output(t_token *tokens, t_shell *shell)
{
	int	fd;

	//make checks for the file name
	shell->cmds->output->file = tokens->next->token;
	if (tokens->type == GREAT)
	{
		shell->cmds->output->type = REDIR_OUTPUT;
		fd = open(shell->cmds->output->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	}
	else if (tokens->type == DGREAT)
	{
		shell->cmds->output->type = REDIR_APPEND;
		fd = open(shell->cmds->output->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	}
	if (fd < 0)
	{
		ft_putstr_fd(shell->cmds->output->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->error_present = true;
	}
	close(fd);
}

void	ft_handle_input(t_token *tokens, t_shell *shell)
{
	if (tokens->type == LESS)
	{
		shell->cmds->input->type = REDIR_INPUT;
		shell->cmds->input->file = tokens->next->token;
		if (access(shell->cmds->input->file, F_OK) != -0)
		{
			ft_putstr_fd("Error with Input files, file does not exist\n", 2);
			shell->error_present = true;
			return ;
		}
	}
	else if (tokens->type == DLESS)
	{
		shell->cmds->input->type = REDIR_HEREDOC;
		shell->cmds->input->file = ft_heredoc(tokens->next->token, shell);
	}
}

void	ft_handle_redir(t_token *tokens, t_shell *shell)
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
		ft_handle_output(tokens, shell);
	}
	if (tokens->type == LESS || tokens->type == DLESS)
	{
		ft_handle_input(tokens, shell);
	}
}
