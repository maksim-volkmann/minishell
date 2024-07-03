/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:43:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/28 09:01:44 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "./parser.h"
# include "./minishell.h"
# define NOWORD "<>|()& \t\n\'\""
# define NOVAR " \"\'\t\n$/"

// lexer.c

void	ft_lexer(const char *line, t_token **tokens);
void	free_token_list(t_token *head);
void	print_linked_list(t_token *head);

// cases.c

t_token	*ft_if_redi_op(const char *line, int *i);
t_token	*ft_if_pipe(const char *line, int *i);
t_token	*ft_if_par(const char *line, int *i);
t_token	*ft_if_quot(const char *line, int *i);

// cases_2.c

t_token	*ft_if_do_quot(const char *line, int *i);
t_token	*ft_if_and(const char *line, int *i);
t_token	*ft_if_word(const char *line, int *i);
t_token	*ft_if_space(const char *line, int *i);

// helper.c
int		ft_is_separator(char c);
char	*ft_extract_str(char *line, int start, int end);
int		ft_isspace(int c);
void	ft_skip_spaces(const char *line, int *i);

// list_helper.c

t_token	*ft_new_token(char *str, enum e_token_type type);
void	ft_lst_add_token(t_token **tokens, t_token *new_token);
void	merge_tokens(t_token **head);
void	remove_current_token(t_token **head, t_token **current,
			t_token **previous);
void	remove_spaces(t_token **head);

#endif
