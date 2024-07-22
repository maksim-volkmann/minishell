/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:48:41 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/21 17:23:46 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/redirections.h"
#include "../../includes/heredoc.h"
#include <stdio.h>
#include <sys/fcntl.h>

int	ft_open_file(char *filename, char *content, t_shell *shell)
{
	int		fd;
	ssize_t	bytes_written;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		exit(EXIT_FAILURE);
	}
	content = ft_append_newline(content);
	content = ft_expander_hd(content, shell);
	bytes_written = write(fd, content, ft_strlen(content));
	if (bytes_written == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (fd);
}

char	*ft_seg_heredoc(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	start = (*i);
	while (input[*i] != '\0' && input[*i] != '\"' && input[*i] != '\'')
	{
		i++;
	}
	end = (*i);
	segment = ft_extract_str(input, start, end);
	return (segment);
}

char	*ft_dq_heredoc(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	i++;
	start = (*i);
	while (input[*i] != '\0' && input[*i] != '\"')
	{
		i++;
	}
	end = (*i);
	segment = ft_extract_str(input, start, end);
	return (segment);
}

char	*ft_sq_heredoc(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	i++;
	start = (*i);
	while (input[*i] != '\0' && input[*i] != '\'')
	{
		i++;
	}
	end = (*i);
	segment = ft_extract_str(input, start, end);
	return (segment);
}
