/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:53:27 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/24 20:31:27 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "executor.h"
# include "minishell.h"
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

//cd.c
int		update_pwd(t_env **env_list, char *old_pwd);
int		change_to_home(t_env **env_list);
int		change_directory(char *path, char *old_pwd, t_env **env_list);
int		execute_cd(char **args, t_env **env_list);

//echo.c
bool	check_newline_flag(char **argv, int *i);
void	execute_echo(char **argv);

//env.c
void	print_envs(t_env *env_list);
int		execute_env(char **args, t_env *env_list);

//exit.c
int		count_args(char **argv);
bool	is_valid_number(char *arg);
int		execute_exit(char **argv, t_shell *shell);

//export.c
void	handle_equal_sign(char *arg, t_env **env_list, t_shell *shell);
char	*find_plus_equal(const char *str);
void	handle_export_arg(char *arg, t_env **env_list, t_shell *shell);
void	print_export_vars(t_env *env_list);
void	execute_export(char **args, t_env **env_list, t_shell *shell);

//export_utils.c
void	handle_plus_equal(char *arg, t_env **env_list, t_shell *shell);
void	find_and_update_var(t_env **env_list, char *key, char *value);
void	update_existing_var(t_env *current, char *value);
int		is_valid_var_name(const char *name);
void	reduce_white_space(char *str);

//export_utils2.c
void	update_env_var(t_env **env_list, const char *key, const char *value);
void	copy_word(char **dst, char **src, int *in_word);
void	print_invalid_identifier(char *arg, t_shell *shell);
void	handle_no_equal_sign(char *arg, t_env **env_list, t_shell *shell);
void	skip_white_space(char **src);

//pwd.c
void	execute_pwd(void);

//unset.c
void	remove_env_var(t_env **env_list, const char *key);
void	execute_unset(char **args, t_env **env_list, t_shell *shell);

#endif
