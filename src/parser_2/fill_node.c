/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:48:08 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/06 09:46:14 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	ft_darray_size(t_token	*tokens)
{
	t_token	*current;
	int		i;

	current = (tokens);
	i = 0;
	while (current != NULL && current->type != PIPE)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	**ft_get_darray(t_token **tokens)
{
	t_token	*current;
	char	**darray;
	int		size;
	int		i;

	current = (*tokens);
	size = ft_darray_size(*tokens);
	i = 0;
	darray = malloc(sizeof(char *) * (size + 1));
	if (!darray)
		return (NULL);
	while (current != NULL && current->type != PIPE)
	{
		darray[i] = current->token;
		i++;
		current = current->next;
	}
	darray[i] = NULL;
	return (darray);
}

int	check_for_output(char **cmd, int current)
{
	if (ft_strcmp(cmd[current], ">") == 0 || ft_strcmp(cmd[current], ">>") == 0)
	{
		if (cmd[current + 1] != NULL)
		{
			return (1);
		}
		return (0);
	}
	return (0);
}

void	ft_handle_files(t_redirection *new_n, char **cmd, int actual)
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
			ft_handle_files(new, cmd, i);
		}
		i++;
	}
	return (new);
}
