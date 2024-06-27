#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include "./lexer.h"
# include <stdbool.h>

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
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_shell
{
	t_command	*cmds;
	t_env_var	*env_list;
	int			exit_code;
	bool		error_present;
}	t_shell;

// parser.c
void			ft_parser(t_shell *shell, t_token **tokens);
void			print_command(t_command *cmd);
void			print_redirection(t_redirection *redir);

// list_helper.c
t_command		*ft_new_node(void);
void			add_or_init_node(t_command **cmds, t_command *new_n);

// darray.c
int				ft_darray_size(t_token	*tokens);
char	**ft_get_darray(t_token **tokens, t_shell **shell, t_redirection *input, t_redirection *output);

// handle_redir.c
void			ft_handle_redir(t_token *tokens, t_shell *shell, t_redirection *input, t_redirection *output);
void			ft_handle_input(t_token *tokens, t_shell *shell, t_redirection *input);
void			ft_handle_output(t_token *tokens, t_shell *shell, t_redirection *output);

// free.c
void			free_redirection(t_redirection *redir);
void			free_command(t_command *cmd);

// helper.c
char			*ft_heredoc_join(char *s1, char *s2);
int				ft_open_file(char *filename, char *content);
char			*ft_heredoc(char *delimiter, t_shell *shell);
int				ft_check_filepath(char *filepath);

#endif
