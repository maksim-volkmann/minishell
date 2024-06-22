#ifndef BUILTINS_H
#define BUILTINS_H

#include "executor.h"


void	ft_echo(char **args, t_env_var *env_list);

int		update_pwd(t_env_var **env_list, char *old_pwd);
int		change_to_home(t_env_var **env_list);
// int ft_cd(char **args, t_env_var **env_list, t_shell *shell);
int ft_cd(char **args, t_env_var **env_list);

void ft_pwd(void);
void ft_export(char **args, t_env_var **env_list);
void ft_unset(char **args, t_env_var **env_list);
void ft_exit(char **args);



void print_env_error(char *arg);
int ft_env(char **args, t_shell *shell);

int ft_strisnum(const char *str);
char *get_env_value(t_env_var *env_list, const char *key);
void add_env_var(t_env_var **env_list, const char *key, const char *value);
void update_env_var(t_env_var **env_list, const char *key, const char *value);
void print_env_vars(t_env_var *env_list);

#endif
