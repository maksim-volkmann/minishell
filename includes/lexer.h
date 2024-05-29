/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:43:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/29 10:33:28 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type
{
	LESS = 1,
	GREAT = 2,
	PIPE = 3,
	LPAR = 4,
	RPAR = 5,
	WORD = 6,
	QUOTE = 7,
	DQUOTE = 8,
	DLESS = 9,
	DGREAT = 10,
	IF_AND = 11,
	IF_OR = 12,
	NUM = 13,
	SPACES = 14,
} t_token_type;

typedef struct s_token
{
	struct s_token	*prev;
	char				*token;
	enum e_token_type	type;
	struct s_token	*next;
}	t_token;

// tokens.c

void	ft_get_tokens(const char *line, t_token **tokens);
void free_token_list(t_token *head);
void print_linked_list(t_token *head);

// cases.c

char	*ft_extract_str(char *line, int start, int end);
t_token	*ft_if_redi_op(t_token **tokens, const char *line, int *i);
t_token	*ft_if_pipe(t_token **tokens, const char *line, int *i);
t_token	*ft_if_par(t_token **tokens, const char *line, int *i);
t_token	*ft_if_quot(t_token **tokens, const char *line, int *i);

// cases_2.c

t_token *ft_if_do_quot(t_token **tokens, const char *line, int *i);

// list_helper.c

t_token	*ft_new_token(char *str, enum e_token_type type);
t_token	*ft_lst_add_token(t_token **tokens, t_token *new_token);
int		ft_strcmp(const char *s1, const char *s2);

#endif
