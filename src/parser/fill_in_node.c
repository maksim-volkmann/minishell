/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:46:20 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/06 13:06:13 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	check_for_input(char **cmd, int current)
{
	if (ft_strcmp(cmd[current], "<") == 0)
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

void	ft_handle_in_files(t_redirection *new_n, char **cmd, int actual)
{
	int	fd;

	new_n->file = cmd[actual + 1];
	if (ft_strcmp(cmd[actual], "<") == 0)
	{
		new_n->type = REDIR_INPUT;
		if (access(new_n->file, F_OK) != -0)
		{
			ft_putstr_fd("Error with Input files, file does not exist\n", 2);
			return ;
		}
	}
	else if (ft_strcmp(cmd[actual], "<<") == 0)
	{
		new_n->type = REDIR_HEREDOC;
		ft_putstr_fd("Error, HEREDOC hass not been yet implemented\n", 1);
		return ;
	}
	else
		return ;
}

t_redirection	*ft_fill_input(char **cmd)
{
	t_redirection	*new;
	int				i;

	new = malloc(sizeof(t_redirection));
	if (!new)
		return (NULL);
	new->type = REDIR_NONE;
	new->file = NULL;
	i = 0;
	while (cmd[i] != NULL)
	{
		if (check_for_input(cmd, i) == 1)
		{
			ft_handle_in_files(new, cmd, i);
		}
		i++;
	}
	return (new);
}
