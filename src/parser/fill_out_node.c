/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_out_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:48:08 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/06 13:04:29 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	check_for_output(char **cmd, int current)
{
	if (ft_strcmp(cmd[current], ">") == 0 || ft_strcmp(cmd[current], ">>") == 0)
	{
		if (cmd[current + 1] != NULL
			&& ft_strcmp(cmd[current + 1], "|") != 0)
		{
			return (1);
		}
		return (0);
	}
	return (0);
}

void	ft_handle_out_files(t_redirection *new_n, char **cmd, int actual)
{
	int	fd;

	new_n->file = cmd[actual + 1];
	if (ft_strcmp(cmd[actual], ">") == 0)
	{
		new_n->type = REDIR_OUTPUT;
		fd = open(new_n->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (ft_strcmp(cmd[actual], ">>") == 0)
	{
		new_n->type = REDIR_APPEND;
		fd = open(new_n->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
		return ;
	if (fd < 0)
	{
		ft_putstr_fd("Error opening file\n", 2);
		free(new_n);
		new_n = NULL;
		return ;
	}
	close(fd);
}

t_redirection	*ft_fill_output(char **cmd)
{
	t_redirection	*new;
	int				i;

	new = malloc(sizeof(t_redirection));
	if (!new)
	{
		return (NULL);
	}
	new->type = REDIR_NONE;
	new->file = NULL;
	i = 0;
	while (cmd[i] != NULL)
	{
		if (check_for_output(cmd, i) == 1)
		{
			ft_handle_out_files(new, cmd, i);
		}
		i++;
	}
	return (new);
}
