/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:48:41 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/02 11:56:34 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include <stdio.h>
#include <sys/fcntl.h>

int	ft_check_filepath(char *filepath)
{
	char	*dir_path;
	char	*last_slash;

	dir_path = ft_strdup(filepath);
	last_slash = strrchr(dir_path, '/');
	if (last_slash != NULL)
	{
		*last_slash = '\0';
	}
	else
	{
		free(dir_path);
		return (1);
	}
	if (access(dir_path, W_OK) == 0)
	{
		free(dir_path);
		return (1);
	}
	else
	{
		free(dir_path);
		return (0);
	}
}

int	ft_open_file(char *filename, char *content, t_shell *shell)
{
	int		fd;
	ssize_t	bytes_written;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		shell->error_present = true;
		exit(EXIT_FAILURE);
	}
	bytes_written = write(fd, content, ft_strlen(content));
	if (bytes_written == -1)
	{
		shell->error_present = true;
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

	if (!segment)
		return (NULL);
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

	if (!segment)
		return (NULL);
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

	if (!segment)
		return (NULL);
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
