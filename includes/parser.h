/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:33:59 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/05 15:44:01 by adrherna         ###   ########.fr       */
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

char		***ft_tarray(t_token **tokens);
char		***ft_tarray_malloc(t_token	**tokens);
void		ft_extract_cmd(t_token **tokens, char ***cmds);
void		ft_fill_array(t_token **tokens, char ***cmds);

// list_helper.c

t_command	*ft_new_node(char **cmd);
void		add_or_init_node(t_command **cmds, t_command *new_n);

// pop_struct.c

void		ft_pop_struct(t_command	**cmds, char ***tarray);
void		ft_check_out_file(t_command **cmd);

void		print_command(t_command *cmd);
void		print_redirection(const char *prefix, t_redirection *redir);

// helper_pop.c

void		set_output_redirection(t_command **cmd, int i);
void		set_input_redirection(t_command **cmd, int i);
int			check_out_file(t_command **cmd);
int			check_input_file(t_command **cmd);

#endif