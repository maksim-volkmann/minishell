#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

// #include "executor.h"
// #include "builtins.h"
// #include "parser.h"
// #include "lexer.h"
// #include "minishell.h"
// #include "redirections.h"
// #include <stdbool.h>
// #include <stdio.h>
// #include <signal.h>
// #include <termios.h>
// #include <readline/readline.h>
// #include <readline/history.h>

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
	SPACES = 13
}	t_token_type;

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
	t_redir_type		type;
	char				*file;
}	t_redir;

typedef struct s_command
{
	char				**argv;
	t_redir				*input;
	t_redir				*output;
	struct s_command	*next;
}	t_cmd;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env;

typedef struct s_token
{
	char				*token;
	enum e_token_type	type;
	struct s_token		*next;
}	t_token;

typedef struct s_shell
{
	t_cmd		*cmds;
	t_env		*env_list;
	t_token		*tokens;
	int			exit_code;
	bool		syn_err_present;
	char		*input;
	bool		child_running;
}	t_shell;

int		ft_strcmp(const char *s1, const char *s2);
int	is_builtin(char *command);

extern volatile int child_running;

// helper.c

void	leaks(void);
void free_env_vars(t_env *env_list);
const char* get_token_type_string(t_token_type type);
void print_token_list(t_token *head);
const char* redir_type_to_string(t_redir_type type);
void print_redir(t_redir *redir);
void print_cmd(t_cmd *cmd);
void add_env_var(t_env **env_list, const char *key, const char *value);
void copy_env_vars(t_shell *shell, char **env);
void print_cmd_details(t_cmd *cmds);
void print_envs(t_env *env_list);



void	prnt_err(const char *cmd, const char *msg, int code, t_shell *shell);




//single_helper.c
int	is_builtin(char *command);
int	file_err(const char *file, t_shell *shell);



void setup_child_signal_handlers(void);


#endif
