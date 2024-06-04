/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:33:59 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/04 10:11:50 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/lexer.h"

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redirection
{
	t_redir_type	type;
	char			*file;
}	t_redirection;

typedef struct s_command
{
	char				**argv;
	t_redirection		*input;
	t_redirection		*output;
	struct s_command	*next;
}	t_command;

// parser.c

void		ft_parser(t_token **tokens, t_command *cmds);
void		ft_print_cmds(char ***cmds);

// tarray.c

void		ft_tarray(t_token **tokens, char ***cmds);
char		***ft_tarray_malloc(t_token	**tokens);
void		ft_extract_cmd(t_token **tokens, char ***cmds);
void		ft_fill_array(t_token **tokens, char ***cmds);

// list_helper.c

t_command	*ft_new_node(char **cmd);
void		add_or_init_node(t_command **cmds, t_command *new_n);

#endif