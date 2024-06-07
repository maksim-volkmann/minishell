// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/wait.h>
// #include <string.h>
// #include "libft/include/libft.h" // Assuming your libft contains necessary functions

// typedef enum e_redir_type {
//     REDIR_NONE,
//     REDIR_INPUT,
//     REDIR_OUTPUT,
//     REDIR_APPEND,
//     REDIR_HEREDOC
// } t_redir_type;

// typedef struct s_redirection {
//     t_redir_type type;
//     char *file;
//     struct s_redirection *next;
// } t_redirection;

// typedef struct s_command {
//     char **argv;
//     t_redirection *input;
//     t_redirection *output;
//     struct s_command *next;
// } t_command;

// typedef struct s_pipeline {
//     t_command *commands;
//     struct s_pipeline *next;
// } t_pipeline;


// // 1
// // t_pipeline
// // └── t_command (Command 1: ls -l)
// //     ├── argv: ["ls", "-l", NULL]
// //     ├── input: NULL
// //     ├── output: NULL
// //     └── next:
// //         └── t_command (Command 2: grep "main")
// //             ├── argv: ["grep", "main", NULL]
// //             ├── input: NULL
// //             ├── output:
// //             │   └── t_redirection
// //             │       ├── type: REDIR_OUTPUT
// //             │       ├── file: "out.txt"
// //             │       └── next: NULL
// //             └── next:
// //                 └── t_command (Command 3: wc -l)
// //                     ├── argv: ["wc", "-l", NULL]
// //                     ├── input: NULL
// //                     ├── output: NULL
// //                     └── next: NULL


// // 2
// // └── t_command (Command 1: cat)
// //     ├── argv: ["cat", NULL]
// //     ├── input:
// //     │   └── t_redirection
// //     │       ├── type: REDIR_INPUT
// //     │       ├── file: "in.txt"
// //     │       └── next: NULL
// //     ├── output: NULL
// //     └── next:
// //         └── t_command (Command 2: grep line)
// //             ├── argv: ["grep", "line", NULL]
// //             ├── input: NULL
// //             ├── output:
// //             │   └── t_redirection
// //             │       ├── type: REDIR_OUTPUT
// //             │       ├── file: "out.txt"
// //             │       └── next: NULL
// //             └── next: NULL



// // Functions to create and add elements to the structures
// t_redirection *create_redirection(t_redir_type type, char *file) {
//     t_redirection *new_redir = (t_redirection *)malloc(sizeof(t_redirection));
//     if (!new_redir) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     new_redir->type = type;
//     new_redir->file = strdup(file);
//     new_redir->next = NULL;
//     return new_redir;
// }

// void add_redirection(t_redirection **redir_list, t_redir_type type, char *file) {
//     t_redirection *new_redir = create_redirection(type, file);
//     if (*redir_list == NULL) {
//         *redir_list = new_redir;
//     } else {
//         t_redirection *current = *redir_list;
//         while (current->next) {
//             current = current->next;
//         }
//         current->next = new_redir;
//     }
// }

// char **duplicate_argv(char **argv) {
//     int argc = 0;
//     while (argv[argc]) {
//         argc++;
//     }

//     char **new_argv = (char **)malloc(sizeof(char *) * (argc + 1));
//     if (!new_argv) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }

//     for (int i = 0; i < argc; i++) {
//         new_argv[i] = strdup(argv[i]);
//     }
//     new_argv[argc] = NULL;

//     return new_argv;
// }

// t_command *create_command(char **argv) {
//     t_command *new_cmd = (t_command *)malloc(sizeof(t_command));
//     if (!new_cmd) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     new_cmd->argv = duplicate_argv(argv);
//     new_cmd->input = NULL;
//     new_cmd->output = NULL;
//     new_cmd->next = NULL;
//     return new_cmd;
// }

// void add_command(t_command **head, char **argv) {
//     t_command *new_cmd = create_command(argv);
//     if (*head == NULL) {
//         *head = new_cmd;
//     } else {
//         t_command *current = *head;
//         while (current->next) {
//             current = current->next;
//         }
//         current->next = new_cmd;
//     }
// }

// t_pipeline *create_pipeline() {
//     t_pipeline *new_pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
//     if (!new_pipeline) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     new_pipeline->commands = NULL;
//     new_pipeline->next = NULL;
//     return new_pipeline;
// }

// void add_pipeline(t_pipeline **head) {
//     t_pipeline *new_pipeline = create_pipeline();
//     if (*head == NULL) {
//         *head = new_pipeline;
//     } else {
//         t_pipeline *current = *head;
//         while (current->next) {
//             current = current->next;
//         }
//         current->next = new_pipeline;
//     }
// }

// // Create command path
// char *create_cmd_path(char *dir, char *cmd) {
//     char *path = ft_strjoin(dir, "/");
//     char *full_path = ft_strjoin(path, cmd);
//     free(path);
//     return full_path;
// }

// // Check command in paths
// char *check_command_in_paths(char **paths, char *cmd) {
//     char *full_path;
//     int i = 0;
//     while (paths[i]) {
//         full_path = create_cmd_path(paths[i], cmd);
//         if (access(full_path, X_OK) == 0) {
//             return full_path;
//         }
//         free(full_path);
//         i++;
//     }
//     return NULL;
// }

// void ft_free_split(char **arr) {
//     int i = 0;

//     if (!arr) {
//         return;
//     }

//     while (arr[i]) {
//         free(arr[i]);
//         i++;
//     }
//     free(arr);
// }

// // Find correct path for the command
// char *find_correct_path(char *cmd, char **env) {
//     char *path_var = NULL;
//     char **paths;
//     char *correct_path;
//     int i = 0;

//     while (env[i]) {
//         if (ft_strncmp(env[i], "PATH=", 5) == 0) {
//             path_var = env[i] + 5;
//             break;
//         }
//         i++;
//     }

//     if (!path_var) {
//         return NULL;
//     }

//     paths = ft_split(path_var, ':');
//     correct_path = check_command_in_paths(paths, cmd);
//     ft_free_split(paths);

//     return correct_path;
// }

// // Execute command
// void execute_command(char *cmd[], char **env) {
//     char *executable_path;

//     if (ft_strchr(cmd[0], '/') != NULL) {
//         executable_path = ft_strdup(cmd[0]);
//     } else {
//         executable_path = find_correct_path(cmd[0], env);
//         if (executable_path == NULL) {
//             fprintf(stderr, "command not found: %s\n", cmd[0]);
//             exit(EXIT_FAILURE);
//         }
//     }
//     execve(executable_path, cmd, env);
//     perror("execve failed");
//     free(executable_path);
//     exit(EXIT_FAILURE);
// }

// // Sets up redirections for a child process and executes the command
// void setup_child(int input_fd, int output_fd, char *cmd[], char **env) {
//     // If input_fd is valid, redirect stdin to input_fd
//     if (input_fd != -1) {
//         if (dup2(input_fd, STDIN_FILENO) == -1) {
//             perror("dup2 input_fd");
//             exit(EXIT_FAILURE);
//         }
//         close(input_fd); // Close the duplicated file descriptor
//     }

//     // If output_fd is valid, redirect stdout to output_fd
//     if (output_fd != -1) {
//         if (dup2(output_fd, STDOUT_FILENO) == -1) {
//             perror("dup2 output_fd");
//             exit(EXIT_FAILURE);
//         }
//         close(output_fd); // Close the duplicated file descriptor
//     }

//     // Execute the command
//     execute_command(cmd, env);
// }

// // Parsing example command: "ls -l | grep pipe > out.txt"
// // void parse_example(t_pipeline **pipelines) {
// //     // Create the first pipeline
// //     add_pipeline(pipelines);
// //     t_pipeline *pl = *pipelines;

// //     // First command: "ls -l"
// //     add_command(&pl->commands, (char *[]) {"ls", "-l", NULL});

// //     // Second command: "grep pipe > out.txt"
// //     t_command *cmd2 = create_command((char *[]) {"grep", "pipe", NULL});
// //     add_redirection(&cmd2->output, REDIR_OUTPUT, "out.txt");
// //     pl->commands->next = cmd2;

// //     // Third command: "wc -l"
// //     // add_command(&pl->commands, (char *[]) {"wc", "-l", NULL});
// // }

// void parse_example(t_pipeline **pipelines) {
//     // Create the first pipeline
//     add_pipeline(pipelines);
//     t_pipeline *pl = *pipelines;

//     // First command: "cat < in.txt"
//     t_command *cmd1 = create_command((char *[]) {"cat", NULL});
//     add_redirection(&cmd1->input, REDIR_INPUT, "in.txt");
//     pl->commands = cmd1;

// 	t_command *cmd2 = create_command((char *[]) {"grep", "line", NULL});
// 	cmd1->next = cmd2;
//     // Second command: "grep line > out.txt"
//     t_command *cmd3 = create_command((char *[]) {"grep", "this", NULL});
//     add_redirection(&cmd3->output, REDIR_OUTPUT, "out.txt");
//     cmd2->next = cmd3;
// }


// // Execute commands in the pipelines
// void execute_pipeline(t_pipeline *pipeline, char **env) {
//     int pipe_fd[2];
//     int input_fd = -1;
//     pid_t pid;

//     t_command *cmd = pipeline->commands;
//     while (cmd) {
//         if (cmd->next != NULL) {
//             if (pipe(pipe_fd) == -1) {
//                 perror("pipe");
//                 exit(EXIT_FAILURE);
//             }
//         } else {
//             pipe_fd[0] = -1;
//             pipe_fd[1] = -1;
//         }

//         pid = fork();
//         if (pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) { // Child process
//             if (input_fd != -1) {
//                 if (dup2(input_fd, STDIN_FILENO) == -1) {
//                     perror("dup2 input_fd");
//                     exit(EXIT_FAILURE);
//                 }
//                 close(input_fd);
//             }

//             if (pipe_fd[1] != -1) {
//                 if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
//                     perror("dup2 pipe_fd[1]");
//                     exit(EXIT_FAILURE);
//                 }
//                 close(pipe_fd[1]);
//             }

//             if (cmd->output != NULL) {
//                 int fd = -1;
//                 if (cmd->output->type == REDIR_OUTPUT) {
//                     fd = open(cmd->output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//                 } else if (cmd->output->type == REDIR_APPEND) {
//                     fd = open(cmd->output->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//                 }
//                 if (fd != -1) {
//                     if (dup2(fd, STDOUT_FILENO) == -1) {
//                         perror("dup2 redirection file");
//                         exit(EXIT_FAILURE);
//                     }
//                     close(fd);
//                 } else {
//                     perror("open redirection file");
//                     exit(EXIT_FAILURE);
//                 }
//             }

//             if (cmd->input != NULL) {
//                 int fd = open(cmd->input->file, O_RDONLY);
//                 if (fd == -1) {
//                     perror("open input redirection file");
//                     exit(EXIT_FAILURE);
//                 }
//                 if (dup2(fd, STDIN_FILENO) == -1) {
//                     perror("dup2 input redirection file");
//                     exit(EXIT_FAILURE);
//                 }
//                 close(fd);
//             }

//             // Execute the command
//             execute_command(cmd->argv, env);
//         }

//         if (input_fd != -1) {
//             close(input_fd);
//         }
//         if (pipe_fd[1] != -1) {
//             close(pipe_fd[1]);
//         }
//         input_fd = pipe_fd[0];

//         cmd = cmd->next;
//     }
//     while (wait(NULL) > 0);
// }

// // Free allocated memory
// void free_pipeline(t_pipeline *pipeline) {
//     t_command *cmd;
//     t_command *tmp_cmd;
//     t_redirection *redir;
//     t_redirection *tmp_redir;

//     while (pipeline) {
//         cmd = pipeline->commands;
//         while (cmd) {
//             tmp_cmd = cmd;
//             cmd = cmd->next;

//             redir = tmp_cmd->input;
//             while (redir) {
//                 tmp_redir = redir;
//                 redir = redir->next;
//                 free(tmp_redir->file); // Free the file name
//                 free(tmp_redir);
//             }

//             redir = tmp_cmd->output;
//             while (redir) {
//                 tmp_redir = redir;
//                 redir = redir->next;
//                 free(tmp_redir->file); // Free the file name
//                 free(tmp_redir);
//             }

//             for (int i = 0; tmp_cmd->argv[i]; i++) {
//                 free(tmp_cmd->argv[i]); // Free each argument
//             }
//             free(tmp_cmd->argv); // Free the argv array
//             free(tmp_cmd); // Free the command node
//         }

//         t_pipeline *tmp_pipeline = pipeline;
//         pipeline = pipeline->next;
//         free(tmp_pipeline); // Free the pipeline node
//     }
// }

// int main(int argc, char **argv, char **env) {
//     (void)argc; // Suppress unused parameter warning
//     (void)argv; // Suppress unused parameter warning

//     t_pipeline *pipelines = NULL;

//     parse_example(&pipelines);

//     t_pipeline *current_pipeline = pipelines;
//     while (current_pipeline) {
//         execute_pipeline(current_pipeline, env);
//         current_pipeline = current_pipeline->next;
//     }

//     // Free the allocated memory
//     free_pipeline(pipelines);

//     return 0;
// }
