/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_proc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:12:29 by goldman           #+#    #+#             */
/*   Updated: 2024/07/22 16:12:45 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"
// #include "../includes/executor.h"


// void	perform_dup_and_close(int old_fd, int new_fd, const char *error_msg, t_shell *shell)
// {
// 	if (old_fd != -1)
// 	{
// 		if (dup2(old_fd, new_fd) == -1)
// 		{
// 			perror(error_msg);
// 			shell->exit_code = 1;
// 			exit(shell->exit_code);
// 		}
// 		close(old_fd);
// 	}
// }

// void	child_proc(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fd[2])
// {
// 	reset_child_signal_handlers(); // Reset signal handling to default
// 	perform_dup_and_close(input_fd, STDIN_FILENO, "dup2 input_fd", shell);
// 	perform_dup_and_close(pipe_fd[1], STDOUT_FILENO, "dup2 pipe_fd[1]", shell);
// 	if (pipe_fd[0] != -1)
// 		close(pipe_fd[0]);
// 	setup_input_redir(cmd->input, shell);
// 	setup_output_redir(cmd->output, shell);
// 	if (handle_builtin(cmd, shell) == -1)
// 		execute_command(cmd, shell->env_list);
// 	exit(shell->exit_code);
// }


// void	parent_proc(int *input_fd, int pipe_fd[2])
// {
// 	if (*input_fd != -1)
// 		close(*input_fd);
// 	if (pipe_fd[1] != -1)
// 		close(pipe_fd[1]);
// 	*input_fd = pipe_fd[0];
// }













#include "../includes/minishell.h"
#include "../includes/executor.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// Function to perform dup2 and close file descriptors
void perform_dup_and_close(int old_fd, int new_fd, const char *error_msg, t_shell *shell)
{
    if (old_fd != -1)
    {
        if (dup2(old_fd, new_fd) == -1)
        {
            perror(error_msg);
            shell->exit_code = 1;
            exit(shell->exit_code);
        }
        close(old_fd);
    }
}

// Function to reset signal handlers to default in the child process
void reset_child_signal_handlers(void) {
    struct sigaction sa;

    sa.sa_handler = SIG_DFL;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    // printf("CHILD: Signal handlers reset to default\n"); // Debug print
}

void child_proc(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fd[2])
{
    reset_child_signal_handlers(); // Reset signal handling to default

    perform_dup_and_close(input_fd, STDIN_FILENO, "dup2 input_fd", shell);
    perform_dup_and_close(pipe_fd[1], STDOUT_FILENO, "dup2 pipe_fd[1]", shell);
    if (pipe_fd[0] != -1)
        close(pipe_fd[0]);

    setup_input_redir(cmd->input, shell);
    setup_output_redir(cmd->output, shell);

    if (handle_builtin(cmd, shell) == -1)
        execute_command(cmd, shell->env_list);
    exit(shell->exit_code);
}

void parent_proc(int *input_fd, int pipe_fd[2])
{
    if (*input_fd != -1)
        close(*input_fd);
    if (pipe_fd[1] != -1)
        close(pipe_fd[1]);
    *input_fd = pipe_fd[0];
}

void wait_for_last_process(pid_t last_pid, t_shell *shell)
{
    int status;
    pid_t pid;

    waitpid(last_pid, &status, 0);
    if (WIFEXITED(status))
        shell->exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        shell->exit_code = WTERMSIG(status) + 128;
        if (WTERMSIG(status) == SIGINT) // Check if the child was terminated by SIGINT
        {
            write(1, "\n", 1); // Print a new line to ensure proper prompt appearance
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
            printf("PARENT: Child terminated by SIGINT\n"); // Debug print
        }
    }

    pid = wait(NULL);
    while (pid > 0)
    {
        // printf("PARENT: Wait for process %d\n", pid); // Debug print
        pid = wait(NULL);
    }

    shell->child_running = false; // Reset the child_running flag
}

pid_t fork_process(t_cmd *cmd, t_shell *shell, int *input_fd, int pipe_fd[2])
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        child_proc(cmd, shell, *input_fd, pipe_fd);
    }
    else
    {
        shell->child_running = true; // Set the child_running flag in the parent process
        parent_proc(input_fd, pipe_fd);
    }
    return (pid);
}

int create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2])
{
    if (cmd->next != NULL)
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        return (1);
    }
    pipe_fd[0] = -1;
    pipe_fd[1] = -1;
    return (0);
}

void check_input_file(t_cmd *cmd, t_shell *shell)
{
    int fd;

    if (cmd->input && cmd->input->file)
    {
        fd = open(cmd->input->file, O_RDONLY);
        if (fd == -1)
        {
            perror(cmd->input->file);
            shell->exit_code = 1;
            cmd = cmd->next;
            return;
        }
        close(fd);
    }
}

void exec_start(t_cmd *commands, t_shell *shell)
{
    int pipe_fd[2];
    int input_fd;
    t_cmd *cmd;
    pid_t last_pid;

    input_fd = -1;
    cmd = commands;
    while (cmd)
    {
        check_input_file(cmd, shell);
        create_pipe_if_needed(cmd, pipe_fd);
        last_pid = fork_process(cmd, shell, &input_fd, pipe_fd);
        cmd = cmd->next;
    }
    if (input_fd != -1)
        close(input_fd);
    wait_for_last_process(last_pid, shell);
}
