/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:33:59 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/22 18:29:48 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include "./lexer.h"

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
	t_redir_type			type;
	char					*file;
}	t_redirection;

typedef struct s_command
{
	char				**argv;
	t_redirection		*input;
	t_redirection		*output;
	struct s_command	*next;
}	t_command;

typedef struct s_env_var
{
	char	*key;
	char	*value;
	struct	s_env_var *next;
}	t_env_var;

typedef struct s_shell
{
	t_command	*cmds;
	t_env_var	*env_list;
	int			exit_code;
}	t_shell;

// parser.c
void			ft_parser(t_command **cmds, t_token **tokens);
void			print_command(t_command *cmd);
void			print_redirection(t_redirection *redir);

// list_helper.c
t_command		*ft_new_node(void);
void			add_or_init_node(t_command **cmds, t_command *new_n);

// darray.c
int				ft_darray_size(t_token	*tokens);
char			**ft_get_darray(t_token **tokens);

// fill_in_node
t_redirection	*ft_fill_input(char **cmd);
int				check_for_input(char **cmd, int current);
void			ft_handle_in_files(t_redirection *new_n,
					char **cmd, int actual);

// fill_out_node.c
t_redirection	*ft_fill_output(char **cmd);
int				check_for_output(char **cmd, int current);
void			ft_handle_out_files(t_redirection *new_n,
					char **cmd, int actual);

// free.c
void			free_redirection(t_redirection *redir);
void			free_command(t_command *cmd);

#endif
