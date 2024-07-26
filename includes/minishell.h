/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:00:47 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/26 10:53:37 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//TODO: fix this shit, remove anything that is unsed or dead.

# include <stdbool.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_signal_received;

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
}	t_shell;

// env.c
void	free_env_vars(t_env *env_list);
t_env	*create_env_var(const char *key, const char *value);
void	add_env_var(t_env **env_list, const char *key, const char *value);
void	copy_env_vars(t_shell *shell, char **env);

// helper.c
void	ft_process_input(t_shell *shell);
int		ft_expander_and_checker(t_shell *shell);
void	ft_exit(t_shell *shell);
void	update_exit_code(t_shell *shell);
int		ft_strcmp(const char *s1, const char *s2);

// minishell.c
void	ft_init_shell(t_shell *shell, char *env[]);
void	ft_loop_init(t_shell *shell);
void	ft_execution(t_shell *shell);
void	ft_end_loop(t_shell *shell);
int		main(int argc, char **argv, char **env);

// signals/signals.c
void	ft_configure_terminal(void);
void	handle_parent_signal(int signal);
void	parent_signals(void);

// signals/signals_utils.c
void	ignore_sigint(struct sigaction *old_action);
void	restore_sigint(const struct sigaction *old_action);
void	ft_restore_terminal(int i);







// helper.c
char	*get_token_type_string(t_token_type type); //dead?
void	print_token_list(t_token *head);//dead?
char	*redir_type_to_string(t_redir_type type);//dead?
void	prnt_err(const char *cmd, const char *msg,
			int code, t_shell *shell);

//single_helper.c
int		is_builtin(char *command);
int		file_err(const char *file, t_shell *shell);


// int		is_builtin(char *command);
// void	print_envs(t_env *env_list);
// void	print_cmd_details(t_cmd *cmds);
// void	copy_env_vars(t_shell *shell, char **env);
// void	add_env_var(t_env **env_list, const char *key, const char *value);
// void	print_redir(t_redir *redir);//dead?
// void	print_cmd(t_cmd *cmd);//dead?
// void	leaks(void);

#endif
