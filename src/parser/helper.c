/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:48:41 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/27 10:23:51 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

//	ls >"./outfiles/outfile with spaces"

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

int	ft_open_file(char *filename, char *content)
{
	int		fd;
	ssize_t	bytes_written;

	printf("%s\n", content);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	bytes_written = write(fd, content, ft_strlen(content));
	if (bytes_written == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	free(content);
	return (fd);
}

char	*ft_heredoc(char *delimiter, t_shell *shell)
{
	char	*filename;
	char	*line;
	char	*content;

	filename = ft_strdup("./tmp/heredoc");
	content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		content = ft_heredoc_join(line, content);
	}
	if (ft_open_file(filename, content) == -1)
		shell->error_present = true;
	return (filename);
}

char	*ft_heredoc_join(char *s1, char *s2)
{
	char	*constr;
	size_t	i;
	size_t	x;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 2;
	constr = (char *)malloc(sizeof(char) * total_len);
	if (!constr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		constr[i] = s1[i];
		i++;
	}
	constr[i++] = '\n';
	x = 0;
	while (s2[x] != '\0')
		constr[i++] = s2[x++];
	constr[i] = '\0';
	free(s1);
	return (constr);
}
