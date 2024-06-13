/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:51:23 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/13 12:20:24 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./parser.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include <unistd.h>
# include <fcntl.h>

// pipex.c
// void	free_env_vars(t_env_var *env_list);
void	copy_env_vars(t_shell *shell, char **env);
void	add_env_var(t_env_var **env_list, const char *key, const char *value);
char	*find_correct_path(char *cmd, t_env_var *env_list);
void	execute_command(char *cmd[], t_env_var *env_list);
void	execute_commands(t_command *commands, t_env_var *env_list);
void	setup_child(int input_fd, int output_fd, t_command *cmd, t_env_var *env_list);
void	setup_input_redirection(int input_fd, t_redirection *input);
void	setup_output_redirection(int output_fd, t_redirection *output);
void	close_fds(int *input_fd, int *pipe_fd);
void	handle_pipe(int *pipe_fd, t_command *cmd);
void	fork_and_setup(int input_fd, int *pipe_fd, t_command *cmd, t_env_var *env_list);









#endif
