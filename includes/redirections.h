/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:36:47 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/25 18:09:48 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "./minishell.h"

// handle_redir.c
void	ft_handle_output(t_token *tokens, t_redir *output);
void	ft_handle_input(t_token *tokens, t_redir *input);
void	ft_handle_redir(t_token *tokens, t_redir *input,
			t_redir *output);

// helper.c
int		ft_open_file(char *filename, char *content, t_shell *shell);
char	*ft_seg_heredoc(char *input, int *i);
char	*ft_dq_heredoc(char *input, int *i);
char	*ft_sq_heredoc(char *input, int *i);

// heredoc_helper.c
char	*ft_append_newline(char *str);
char	*ft_heredoc_join(char *s1, char *s2);
int		ft_count_delimiters(t_token *tokens);
char	**ft_extract_delimiters(t_token *tokens);

// heredoc.c
int		ft_heredoc_check(t_shell *shell);
void	initialize_heredoc(t_shell *shell, char ***delimiters, int *del_count);
void	process_heredoc(t_shell *shell, char **content,
			char **delimiters, int del_count);
void	ft_heredoc_loop(t_shell *shell);

#endif
