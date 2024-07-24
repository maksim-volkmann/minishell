/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:57:33 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/24 13:51:59 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./parser.h"
# include "./expander.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>

// echo_pwd_cd_env.c
int		execute_echo_builtin(t_cmd *cmd, t_shell *shell);
int		execute_pwd_builtin(t_cmd *cmd, t_shell *shell);
int		execute_cd_builtin(t_cmd *cmd, t_shell *shell);
int		execute_env_builtin(t_cmd *cmd, t_shell *shell);

// export_unset_exit.c
int		execute_export_builtin(t_cmd *cmd, t_shell *shell);
int		execute_unset_builtin(t_cmd *cmd, t_shell *shell);
int		execute_exit_builtin(t_cmd *cmd, t_shell *shell);

// free_here.c
void	ft_free_split(char **arr);

// handle_buildin.c
void	restore_stdout(int saved_stdout);
int		execute_specific_builtin(t_cmd *cmd, t_shell *shell);
int		handle_builtin(t_cmd *cmd, t_shell *shell);

// parent_child_proc.c
void	perform_dup_and_close(int old_fd, int new_fd,
			const char *error_msg, t_shell *shell);
void	child_proc(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fd[2]);
void	parent_proc(int *input_fd, int pipe_fd[2]);

// prepare_env.c
void	free_envp(char **envp);
int		count_envs(t_env *env_list);
char	*create_env_var_string(const char *key, const char *value);
void	free_envp_on_error(char **envp, int i);
char	**prepare_envp(t_env *env_list);

// preperations.c
void	wait_for_last_process(pid_t last_pid, t_shell *shell);
pid_t	fork_process(t_cmd *cmd, t_shell *shell, int *input_fd, int pipe_fd[2]);
int		create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2]);
void	check_input_file(t_cmd *cmd, t_shell *shell);
void	exec_start(t_cmd *commands, t_shell *shell);

// redirections.c
void	setup_input_redir(t_redir *input, t_shell *shell);
void	setup_output_redir(t_redir *output, t_shell *shell);

// start_execve.c
char	*create_cmd_path(char *dir, char *cmd);
char	*get_env_value(t_env *env_list, const char *key);
char	*find_correct_path(char *cmd, t_env *env_list);
char	*get_executable_path(char *cmd, t_env *env_list);
void	execute_command(t_cmd *cmd, t_env *env_list);

// exec_single.c
int		validate_input_no_cmd(t_cmd *cmd, t_shell *shell);
int		validate_output_no_cmd(t_cmd *cmd, t_shell *shell);
int		validate_input_file(t_cmd *cmd, t_shell *shell);
int		validate_output_file(t_cmd *cmd, t_shell *shell);
void	exec_single(t_cmd *cmd, t_shell *shell);

// single_helper.c
int		file_err(const char *file, t_shell *shell);
int		is_builtin(char *command);

#endif
