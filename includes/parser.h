/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:55:59 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/25 17:51:36 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "./minishell.h"

# define NO_DEL ">< \n\t"
# define NOWORD "<>| \t\n\'\""
# define NOVAR " \"\'\t\n$/"

// -> Parser

void		ft_exit(t_shell *shell);
// parser.c
void		ft_parser(t_shell *shell, t_token **tokens);
void		print_cmd(t_cmd *cmd);
void		print_redir(t_redir *redir);

// list_helper.c
t_cmd		*ft_new_node(void);
void		add_or_init_node(t_cmd **cmds, t_cmd *new_n);

// darray.c
int			ft_darray_size(t_token	*tokens);
char		**ft_get_darray(t_token **tokens,
				t_redir *input, t_redir *output);

// handle_redir.c
void		ft_handle_redir(t_token *tokens, t_redir *input,
				t_redir *output);
void		ft_handle_input(t_token *tokens, t_redir *input);
void		ft_handle_output(t_token *tokens, t_redir *output);

// free.c
void		free_redirection(t_redir *redir);
void		free_command(t_cmd *cmd);
void		ft_free_heredoc(char *content, char **delimiters);

// helper.c
int			ft_open_file(char *filename, char *content, t_shell *shell);
int			ft_check_filepath(char *filepath);
char		*ft_seg_heredoc(char *input, int *i);
char		*ft_dq_heredoc(char *input, int *i);
char		*ft_sq_heredoc(char *input, int *i);

// heredoc.c
void		ft_heredoc_loop(t_shell *shell);
char		*ft_append_newline(char *str);




// -> Syntax
int			ft_syntax_checker(t_token *tokens);
int			ft_syntax_checker_2(t_token *tokens);




// -> Lexer

// lexer.c
void		ft_lexer(const char *line, t_shell *shell);
void		free_token_list(t_token *head);
void		print_linked_list(t_token *head);
int			ft_syntax_checker(t_token *tokens);
int			ft_syntax_checker_2(t_token *tokens);

// cases.c
t_token		*ft_if_redi_op(const char *line, int *i, t_shell *shell);
t_token		*ft_if_pipe(const char *line, int *i, t_shell *shell);
t_token		*ft_if_par(const char *line, int *i, t_shell *shell);
t_token		*ft_if_quot(const char *line, int *i, t_shell *shell);

// cases_2.c
t_token		*ft_if_do_quot(const char *line, int *i, t_shell *shell);
t_token		*ft_if_and(const char *line, int *i);
t_token		*ft_if_word(const char *line, int *i);
t_token		*ft_if_space(const char *line, int *i);

// helper.c
int			ft_is_separator(char c);
char		*ft_extract_str(char *line, int start, int end);
int			ft_isspace(int c);
void		ft_skip_spaces(const char *line, int *i);

// list_helper.c
t_token		*ft_new_token(char *str, enum e_token_type type);
void		ft_lst_add_token(t_token **tokens, t_token *new_token);
void		merge_tokens(t_token **head);
void		remove_current_token(t_token **head, t_token **current,
				t_token **previous);
void		remove_spaces(t_token **head);

#endif
