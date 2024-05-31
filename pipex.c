     i = 0;
    t_command *current_cmd = commands;
    while (i < num_commands) {
        pids[i] = fork(); // Fork a new process
        if (pids[i] == -1) { // Check for fork errors
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) { // Child process
            // Setup redirections for the child process
            if (i == 0) {
                // First command: no input redirection
                close(pipe_fds[i][0]); // Close unused read end of the pipe
                setup_child(-1, pipe_fds[i][1], current_cmd->argv, env); // Set up output redirection to the pipe
            } else if (i == num_commands - 1) {
                // Last command: no output redirection
                close(pipe_fds[i - 1][1]); // Close unused write end of the previous pipe
                setup_child(pipe_fds[i - 1][0], -1, current_cmd->argv, env); // Set up input redirection from the previous pipe
            } else {
                // Middle commands: both input and output redirection
                close(pipe_fds[i - 1][1]); // Close previous pipe write end
                close(pipe_fds[i][0]); // Close current pipe read end
                setup_child(pipe_fds[i - 1][0], pipe_fds[i][1], current_cmd->argv, env); // Set up both input and output redirections
            }

            // Close all pipe ends in the child process to avoid hanging
            int j = 0;
            while (j < num_commands - 1) {
                close(pipe_fds[j][0]);
                close(pipe_fds[j][1]);
                j++;
            }
        } else { // Parent process
            if (i > 0) {
                // Close read and write ends of the previous pipe in the parent process
                close(pipe_fds[i - 1][0]);
                close(pipe_fds[i - 1][1]);
            }
        }
        current_cmd = current_cmd->next; // Move to the next command in the list
        i++;
    }

    // Parent process closes all remaining pipe ends
    i = 0;
    while (i < num_commands - 1) {
        close(pipe_fds[i][0]);
        close(pipe_fds[i][1]);
        i++;
    }

    // Wait for all child processes to finish
    i = 0;
    while (i < num_commands) {
        waitpid(pids[i], NULL, 0);
        i++;
    }

    // Free the linked list
    t_command *tmp;
    while (commands) {
        tmp = commands;
        commands = commands->next;
        free(tmp->argv); // Free the argv array
        free(tmp); // Free the command node
    }

    return 0;
}
