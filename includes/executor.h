/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:51:23 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/11 11:44:22 by adrherna         ###   ########.fr       */
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
void	execute_commands(t_command *commands, char **env);
char	*create_cmd_path(char *dir, char *cmd);
void	execute_command(char *cmd[], char **env);
char	*find_correct_path(char *cmd, char **env);
void	setup_child(int input_fd, int output_fd, char *cmd[], char **env, t_redirection *input, t_redirection *output);
void	fork_and_setup(int input_fd, int *pipe_fd, t_command *cmd, char **env);
void	handle_pipe(int *pipe_fd, t_command *cmd);
void	close_fds(int *input_fd, int *pipe_fd);
char	*check_command_in_paths(char **paths, char *cmd);
void	ft_free_split(char **arr);


#endif
