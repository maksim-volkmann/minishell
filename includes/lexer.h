/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:43:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/06 09:26:03 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define NOWORD "<>|()& \t\n"

typedef enum e_token_type
{
	LESS = 0,
	GREAT = 1,
	PIPE = 2,
	LPAR = 3,
	RPAR = 4,
	WORD = 5,
	QUOTE = 6,
	DQUOTE = 7,
	DLESS = 8,
	DGREAT = 9,
	AND = 10,
	DAND = 11,
	NUM = 12,
	SPACES = 13,
} t_token_type;

typedef struct s_token
{
	char				*token;
	enum e_token_type	type;
	struct s_token	*next;
}	t_token;

// lexer.c

void	ft_lexer(const char *line, t_token **tokens);
void	free_token_list(t_token *head);
void	print_linked_list(t_token *head);

// cases.c

t_token	*ft_if_redi_op(t_token **tokens, const char *line, int *i);
t_token	*ft_if_pipe(t_token **tokens, const char *line, int *i);
t_token	*ft_if_par(t_token **tokens, const char *line, int *i);
t_token	*ft_if_quot(t_token **tokens, const char *line, int *i);

// cases_2.c

t_token *ft_if_do_quot(t_token **tokens, const char *line, int *i);
t_token *ft_if_and(t_token **tokens, const char *line, int *i);
t_token *ft_if_word(t_token **tokens, const char *line, int *i);

// helper.c
int	ft_is_separator(char c);
char	*ft_extract_str(char *line, int start, int end);
int ft_strcmp(const char *s1, const char *s2);
void	ft_skip_spaces(const char *line, int *i);

// list_helper.c

t_token	*ft_new_token(char *str, enum e_token_type type);
void	ft_lst_add_token(t_token **tokens, t_token *new_token);
int		ft_strcmp(const char *s1, const char *s2);

#endif
