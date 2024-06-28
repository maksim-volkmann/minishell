// #ifndef EXECUTOR_H
// #define EXECUTOR_H

// #include "./parser.h"
// #include "./expander.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include "../libft/include/libft.h"
// #include <unistd.h>
// #include <fcntl.h>

// // Function declarations
// void exec_start(t_command *commands, t_shell *shell);
// int is_builtin(char *cmd);
// int execute_builtin(t_command *cmd, t_shell *shell, int output_fd);

// // Redirection functions
// void setup_input_redirection(int input_fd, t_redirection *input);
// void setup_output_redirection(int output_fd, t_redirection *output);
// char *create_cmd_path(char *dir, char *cmd);
// char *find_correct_path(char *cmd, t_env_var *env_list);
// void ft_free_split(char **arr);

// #endif


#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./parser.h"
# include "./expander.h"
# include "./lexer.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include <unistd.h>
# include <fcntl.h>

void ft_free_split(char **arr);
char *get_env_value(t_env_var *env_list, const char *key);
char *create_cmd_path(char *dir, char *cmd);
char *find_correct_path(char *cmd, t_env_var *env_list);
void setup_input_redirection(t_redirection *input);
void setup_output_redirection(t_redirection *output);
void print_env_vars(t_env_var *env_list);
void execute_echo(char **argv);
// void execute_pwd(void);
int execute_exit(char **argv, t_shell *shell);
int handle_builtin(t_command *cmd, t_shell *shell);
void execute_command(t_command *cmd, t_env_var *env_list, t_shell *shell);
void fork_and_execute(t_command *cmd, t_env_var *env_list, int input_fd, int output_fd, t_shell *shell);
void exec_start(t_command *commands, t_shell *shell);
void free_command2(t_command *cmd);

#endif
