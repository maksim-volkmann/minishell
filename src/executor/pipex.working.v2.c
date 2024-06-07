// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/wait.h>

// // Assuming these are the functions available in your libft
// #include "libft/include/libft.h"

// // Define the structures
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

// // Functions to create and add elements to the structures

// t_redirection *create_redirection(t_redir_type type, char *file) {
//     t_redirection *new_redir = (t_redirection *)malloc(sizeof(t_redirection));
//     if (!new_redir) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     new_redir->type = type;
//     new_redir->file = file;
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

// t_command *create_command(char **argv) {
//     t_command *new_cmd = (t_command *)malloc(sizeof(t_command));
//     if (!new_cmd) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     new_cmd->argv = argv;
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

// // Parsing example command: "ls -l | grep 2023 >> out.txt | ls -l"
// void parse_example(t_pipeline **pipelines) {
//     add_pipeline(pipelines);
//     t_pipeline *pl = *pipelines;

//     // First command: "ls -l"
//     add_command(&pl->commands, (char *[]) {"ls", "-l", NULL});

//     // Second command: "grep 2023 >> out.txt"
//     add_pipeline(pipelines);
//     pl = pl->next;
//     add_command(&pl->commands, (char *[]) {"grep", "2023", NULL});
//     add_redirection(&pl->commands->output, REDIR_APPEND, "out.txt");

//     // Third command: "ls -l"
//     add_pipeline(pipelines);
//     pl = pl->next;
//     add_command(&pl->commands, (char *[]) {"ls", "-l", NULL});
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

//             execve(cmd->argv[0], cmd->argv, env);
//             perror("execve failed");
//             exit(EXIT_FAILURE);
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

//     return 0;
// }
