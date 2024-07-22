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
// void exec_start(t_cmd *commands, t_shell *shell);
// int is_builtin(char *cmd);
// int execute_builtin(t_cmd *cmd, t_shell *shell, int output_fd);

// // Redirection functions
// void setup_input_redir(int input_fd, t_redir *input);
// void setup_output_redir(int output_fd, t_redir *output);
// char *create_cmd_path(char *dir, char *cmd);
// char *find_correct_path(char *cmd, t_env *env_list);
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

// void ft_free_split(char **arr);
// char *get_env_value(t_env *env_list, const char *key);
// char *create_cmd_path(char *dir, char *cmd);
// char *find_correct_path(char *cmd, t_env *env_list);
// void setup_input_redir(t_redir *input, t_shell *shell);
// void setup_output_redir(t_redir *output, t_shell *shell);
// // void execute_echo(char **argv);
// // void execute_pwd(void);
// int execute_exit(char **argv, t_shell *shell);
// int handle_builtin(t_cmd *cmd, t_shell *shell);
// void execute_command(t_cmd *cmd, t_env *env_list);
// void fork_and_execute(t_cmd *cmd, t_env *env_list, int input_fd, int output_fd, t_shell *shell);
// void exec_start(t_cmd *commands, t_shell *shell);
// void free_command2(t_cmd *cmd);
// char *find_plus_equal(const char *str);
// // int is_builtin(t_cmd *cmd);




void	ft_free_split(char **arr);
char	*get_env_value(t_env *env_list, const char *key);
char	*create_cmd_path(char *dir, char *cmd);
char	*find_correct_path(char *cmd, t_env *env_list);
void	setup_input_redir(t_redir *input, t_shell *shell);
void	setup_output_redir(t_redir *output, t_shell *shell);
int		execute_exit(char **argv, t_shell *shell);
int		handle_builtin(t_cmd *cmd, t_shell *shell);
void	execute_command(t_cmd *cmd, t_env *env_list);
void	fork_and_execute(t_cmd *cmd, t_env *env_list, int input_fd, int output_fd, t_shell *shell);
void	exec_start(t_cmd *commands, t_shell *shell);
void	free_command2(t_cmd *cmd);
char	*find_plus_equal(const char *str);

//redirections.c
void	setup_input_redir(t_redir *input, t_shell *shell);
void	setup_output_redir(t_redir *output, t_shell *shell);

//export_unset_exit.c
int		execute_export_builtin(t_cmd *cmd, t_shell *shell);
int		execute_unset_builtin(t_cmd *cmd, t_shell *shell);
int		execute_exit_builtin(t_cmd *cmd, t_shell *shell);

//handke_buildin.c
void	restore_stdout(int saved_stdout);
int		execute_specific_builtin(t_cmd *cmd, t_shell *shell);
int		handle_builtin(t_cmd *cmd, t_shell *shell);

//env_export_unset_exit.c
int		execute_echo_builtin(t_cmd *cmd, t_shell *shell);
int		execute_pwd_builtin(t_cmd *cmd, t_shell *shell);
int		execute_cd_builtin(t_cmd *cmd, t_shell *shell);
int		execute_env_builtin(t_cmd *cmd, t_shell *shell);


//executor.c
void	exec_start(t_cmd *commands, t_shell *shell);
void	check_input_file(t_cmd *cmd, t_shell *shell);
int		create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2]);
pid_t 	fork_process(t_cmd *cmd, t_shell *shell, int *input_fd, int pipe_fd[2]);
void	wait_for_last_process(pid_t last_pid, t_shell *shell);


//move those:
void	child_proc(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fd[2]);
void	parent_proc(int *input_fd, int pipe_fd[2]);
// void	parent_proc(pid_t last_pid, int *input_fd, int pipe_fd[2]);
char	*ft_strcpy(char *dest, const char *src);

//exec_single.c
int		validate_input_no_cmd(t_cmd *cmd, t_shell *shell);
int		validate_output_no_cmd(t_cmd *cmd, t_shell *shell);
int		validate_input_file(t_cmd *cmd, t_shell *shell);
int		validate_output_file(t_cmd *cmd, t_shell *shell);
void	exec_single(t_cmd *cmd, t_shell *shell);


//prepare_env.c
void	free_envp(char **envp);
int		count_envs(t_env *env_list);
char	*create_env_var_string(const char *key, const char *value);
void	free_envp_on_error(char **envp, int i);
char	**prepare_envp(t_env *env_list);

//start_execve.c
char	*create_cmd_path(char *dir, char *cmd);
char	*get_env_value(t_env *env_list, const char *key);
char	*find_correct_path(char *cmd, t_env *env_list);
char	*get_executable_path(char *cmd, t_env *env_list);
void	execute_command(t_cmd *cmd, t_env *env_list);

//free_here.c
void	ft_free_split(char **arr);



void reset_child_signal_handlers(void);


#endif
