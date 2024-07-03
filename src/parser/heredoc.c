/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:17:44 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/03 15:34:15 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>

char	*ft_append_newline(char *str)
{
	size_t	len;
	char	*new_str;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, len + 1);
	new_str[len] = '\n';
	new_str[len + 1] = '\0';
	return (new_str);
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
	if (ft_strlen(s1) != 0)
		constr[i++] = '\n';
	x = 0;
	while (s2[x] != '\0')
		constr[i++] = s2[x++];
	constr[i] = '\0';
	free(s1);
	return (constr);
}

int	ft_count_delimiters(t_token *tokens)
{
	t_token	*current;
	int		del_count;

	current = tokens;
	del_count = 0;
	while (current != NULL)
	{
		if (current->type == DLESS)
			del_count++;
		current = current->next;
	}
	return (del_count);
}

char	**ft_extract_delimiters(t_token *tokens)
{
	char		**delimiters;
	const int	len = ft_count_delimiters(tokens);
	int			i;

	delimiters = malloc(sizeof(char *) * (len + 1));
	if (!delimiters)
		return (NULL);
	i = 0;
	while (tokens != NULL)
	{
		if (tokens->type == DLESS)
		{
			if (tokens->next != NULL && tokens->next->type != DLESS
				&& tokens->next->type != LESS && tokens->next->type != GREAT
				&& tokens->next->type != DGREAT)
				delimiters[i++] = tokens->next->token;
			else
				printf("syntax error near unexpected token '<<'\n");
		}
		tokens = tokens->next;
	}
	delimiters[i] = NULL;
	return (delimiters);
}

void	ft_heredoc_loop(t_shell *shell)
{
	char	**delimiters;
	int		del_count;
	char	*content;
	char	*line;
	int		i;

	delimiters = ft_extract_delimiters(shell->tokens);
	del_count = ft_count_delimiters(shell->tokens);
	content = ft_strdup("");
	i = 0;

	if (ft_count_delimiters(shell->tokens) == 0)
		return ;
	while (del_count != 0)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiters[i]) == 0)
		{
			del_count -= 1;
			i++;
		}
		else if (ft_count_delimiters(shell->tokens) > 1 && i >= del_count - 1)
			content = ft_heredoc_join(content, line);
		else if (i >= del_count - 1)
			content = ft_heredoc_join(content, line);
	}
	ft_open_file("./tmp/heredoc.txt", content, shell);
	ft_free_heredoc(content, delimiters);
}

// const char	**ft_extract_delimiters(t_token *tokens)
// {
// 	t_token		*current;
// 	char		**delimiters;
// 	const int	len = ft_count_delimiters(tokens);
// 	int			i;

// 	delimiters = malloc(sizeof(char *) * (len + 1));
// 	i = 0;
// 	while (current != NULL)
// 	{
// 		if (current->type == DLESS)
// 		{
// 			if (current->next != NULL && current->next->type != DLESS
// 				&& current->next->type != LESS && current->next->type != GREAT
// 				&& current->next->type != DGREAT)
// 			{
// 				delimiters[i] = current->token;
// 				printf("|%s|\n", current->token);
// 				i++;
// 			}
// 			else
// 				printf("syntax error near unexpected token '<<'\n");
// 		}
// 		current = current->next;
// 	}
// 	return ((const char **)delimiters);
// }


// void	ft_heredoc(t_token *tokens)
// {
// 	const char	**delimiters = ft_extract_delimiters(tokens);
// 	int			del_count;
// 	char		*content;
// 	char		*line;
// 	int			i;

// 	del_count = ft_count_delimiters(tokens);
// 	content = ft_strdup("");
// 	i = 0;
// 	while (1)
// 	{
// 		if (del_count == 0)
// 			break ;
// 		line = readline("> ");
// 		if (ft_strcmp(line, delimiters[i]) == 0)
// 		{
// 			del_count -= 1;
// 			i++;
// 		}
// 		else if (i >= del_count - 1)
// 			content = ft_heredoc_join(line, content);
// 	}
// 	printf("%s\n", content);
// }

// char	*ft_heredoc(char *delimiter, t_shell *shell)
// {
// 	char	*filename;
// 	char	*line;
// 	char	*content;

// 	filename = ft_strdup("./tmp/heredoc");
// 	content = ft_strdup("");
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		content = ft_heredoc_join(line, content);
// 	}
// 	if (ft_open_file(filename, content) == -1)
// 		shell->error_present = true;
// 	return (filename);
// }

