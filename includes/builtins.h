#ifndef BUILTINS_H
#define BUILTINS_H

#include "executor.h"


void	ft_echo(char **args, t_env_var *env_list);

void	update_pwd(t_env_var **env_list, char *old_pwd);
void	change_to_home(t_env_var **env_list);
void	ft_cd(char **args, t_env_var **env_list);

void ft_pwd(void);
void ft_export(char **args, t_env_var **env_list);
void ft_unset(char **args, t_env_var **env_list);
void ft_exit(char **args);
void ft_env(t_env_var *env_list);

int ft_strisnum(const char *str);
char *get_env_value(t_env_var *env_list, const char *key);
void add_env_var(t_env_var **env_list, const char *key, const char *value);
void update_env_var(t_env_var **env_list, const char *key, const char *value);
void print_env_vars(t_env_var *env_list);

#endif
