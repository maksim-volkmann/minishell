#ifndef BUILTINS_H
#define BUILTINS_H

#include "executor.h"
#include "minishell.h"


// void	execute_echo(char **argv);
// bool	check_newline_flag(char **argv, int *i);

void	update_env_var(t_env_var **env_list, const char *key, const char *value);
int		update_pwd(t_env_var **env_list, char *old_pwd);
bool	check_newline_flag(char **argv, int *i);
void	execute_echo(char **argv);




int		change_to_home(t_env_var **env_list);
void	update_env_var(t_env_var **env_list, const char *key, const char *value);
int		change_to_home(t_env_var **env_list);
int		execute_cd(char **args, t_env_var **env_list);




void	execute_pwd(void);

void	print_env_vars(t_env_var *env_list);
int		execute_env(char **args, t_env_var *env_list);




void	print_export_vars(t_env_var *env_list);
void	reduce_white_space(char *str);
int	is_valid_var_name(const char *name);
char	*find_plus_equal(const char *str);
void	handle_plus_equal(char *arg, t_env_var **env_list, t_shell *shell);
void	handle_equal_sign(char *arg, t_env_var **env_list, t_shell *shell);
void	handle_no_equal_sign(char *arg, t_env_var **env_list, t_shell *shell);
void	handle_export_arg(char *arg, t_env_var **env_list, t_shell *shell);
void	execute_export(char **args, t_env_var **env_list, t_shell *shell);


void	remove_env_var(t_env_var **env_list, const char *key);
void	execute_unset(char **args, t_env_var **env_list, t_shell *shell);

#endif
