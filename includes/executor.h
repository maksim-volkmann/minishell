/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:51:23 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/13 13:39:05 by mvolkman         ###   ########.fr       */
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
void	ft_free_split(char **arr);
void	free_env_vars(t_env_var *env_list);
void	setup_input_redirection(int input_fd, t_redirection *input);
void	setup_output_redirection(int output_fd, t_redirection *output);
void	ft_echo(char **args);
int		is_builtin(char *cmd);
void	execute_builtin(t_command *cmd);
void	execute_command(t_command *cmd, t_env_var *env_list);
void	setup_child(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd);
void	close_fds(int *input_fd, int *pipe_fd);
void	handle_pipe(int *pipe_fd, t_command *cmd);
void	fork_and_setup(int input_fd, int *pipe_fd, t_command *cmd, t_env_var *env_list);
void	execute_commands(t_command *commands, t_env_var *env_list);
char	*find_correct_path(char *cmd, t_env_var *env_list);
char	*create_cmd_path(char *dir, char *cmd);





#endif
