#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "./parser.h"
#include "./expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/include/libft.h"
#include <unistd.h>
#include <fcntl.h>

// Function declarations
void execute_commands(t_command *commands, t_shell *shell);
int is_builtin(char *cmd);
int execute_builtin(t_command *cmd, t_shell *shell, int output_fd);
char *create_cmd_path(char *dir, char *cmd);
char *find_correct_path(char *cmd, t_env_var *env_list);
void ft_free_split(char **arr);
void setup_child(t_command *cmd, t_shell *shell, int input_fd, int output_fd);

// Redirection functions
void setup_input_redirection(int input_fd, t_redirection *input);
void setup_output_redirection(int output_fd, t_redirection *output);

// Pipe handling functions
void handle_pipe(int *pipe_fd, t_command *cmd);
void fork_and_setup(int input_fd, int *pipe_fd, t_command *cmd, t_shell *shell);

#endif
