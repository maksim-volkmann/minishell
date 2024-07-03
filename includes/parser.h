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

void		ft_exit(t_shell *shell);
// parser.c
void		ft_parser(t_shell *shell, t_token **tokens);
void		print_command(t_command *cmd);
void		print_redirection(t_redirection *redir);

// list_helper.c
t_command	*ft_new_node(void);
void		add_or_init_node(t_command **cmds, t_command *new_n);

// darray.c
int			ft_darray_size(t_token	*tokens);
char		**ft_get_darray(t_token **tokens, t_shell **shell,
				t_redirection *input, t_redirection *output);

// handle_redir.c
void		ft_handle_redir(t_token *tokens, t_shell *shell,
				t_redirection *input, t_redirection *output);
void		ft_handle_input(t_token *tokens, t_shell *shell,
				t_redirection *input);
void		ft_handle_output(t_token *tokens, t_shell *shell,
				t_redirection *output);

// free.c
void		free_redirection(t_redirection *redir);
void		free_command(t_command *cmd);
void		ft_free_heredoc(char *content, char **delimiters);

// helper.c
int			ft_open_file(char *filename, char *content, t_shell *shell);
int			ft_check_filepath(char *filepath);
char		*ft_seg_heredoc(char *input, int *i);
char		*ft_dq_heredoc(char *input, int *i);
char		*ft_sq_heredoc(char *input, int *i);

// heredoc.c
void		ft_heredoc_loop(t_shell *shell);
// char		*ft_heredoc_join(char *s1, char *s2);
#endif
