
#include "../includes/executor.h"
#include "../includes/builtins.h"
#include "../includes/parser.h"
#include "../includes/lexer.h"
#include "../includes/minishell.h"
#include <stdio.h>

void	ft_exit(t_shell *shell)
{
	free_env_vars(shell->env_list);
	// free(shell->input);
	exit(shell->exit_code);
}

void	ft_init_shell(t_shell *shell, char *env[])
{
	shell->env_list = NULL;
	copy_env_vars(shell, env);
	shell->exit_code = 0;
}

void	ft_heredoc_check(t_shell *shell)
{
	ft_lexer(shell->input, &shell->tokens);
	ft_heredoc_loop(shell);
	free_token_list(shell->tokens);
	shell->tokens = NULL;
}

int	ft_manage_input(t_shell *shell)
{
	if (!shell->input)
		ft_exit(shell);
	add_history(shell->input);
	ft_heredoc_check(shell);
	shell->input = ft_expander(shell->input, shell);
	if (ft_strcmp(shell->input, "") == 0)
	{
		free(shell->input);
		return (1);
	}
	return (0);
}

int	ft_manage_errors(t_shell *shell)
{
	if (shell->error_present == true)
	{
		free_command(shell->cmds);
		free_token_list(shell->tokens);
		free(shell->input);
		return (1);
	}
	return (0);
}

void print_env_vars(t_env_var *env_list)
{
	t_env_var *current = env_list;
	while (current)
	{
		if (current->value)
		{
			printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
}


void print_command_details(t_command *cmds)
{
    t_command *current_cmd = cmds;
    int i;

    while (current_cmd)
    {
        printf("Command:\n");

        // Print all arguments
        for (i = 0; current_cmd->argv[i]; i++)
        {
            printf("  Arg[%d]: %s\n", i, current_cmd->argv[i]);
        }

        // Print input redirection details if present
        if (current_cmd->input)
        {
            printf("  Input Redirection:\n");
            printf("    Type: %d\n", current_cmd->input->type);
            printf("    File: %s\n", current_cmd->input->file);
        }
        else
        {
            printf("  Input Redirection: None\n");
        }

        // Print output redirection details if present
        if (current_cmd->output)
        {
            printf("  Output Redirection:\n");
            printf("    Type: %d\n", current_cmd->output->type);
            printf("    File: %s\n", current_cmd->output->file);
        }
        else
        {
            printf("  Output Redirection: None\n");
        }

        // Print next command details if present
        if (current_cmd->next)
        {
            printf("  Next Command:\n");
            for (int j = 0; current_cmd->next->argv[j]; j++)
            {
                printf("    Next Arg[%d]: %s\n", j, current_cmd->next->argv[j]);
            }
        }
        else
        {
            printf("  Next Command: None\n");
        }

        current_cmd = current_cmd->next;
    }
}


void	ft_init_shell(t_shell *shell, char *env[])
{
	shell->env_list = NULL;
	copy_env_vars(shell, env);
	shell->exit_code = 0;
}

void	handle_redirection(t_command *cmd)
{
	if (cmd->input)
		setup_input_redirection(cmd->input);
	if (cmd->output)
		setup_output_redirection(cmd->output);
}

int	is_builtin(char *command)
{
	return (ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "exit") == 0);
}
void	execute_single_command(t_command *cmd, t_shell *shell)
{
	if (cmd->argv[0] == NULL)
	{
		if (cmd->input && cmd->input->file)
		{
			if (access(cmd->input->file, F_OK) != 0)
			{
				fprintf(stderr, "minishell: %s: No such file or directory\n", cmd->input->file);
				shell->exit_code = 1;
				return;
			}
		}
		if (cmd->output && cmd->output->file)
		{
			int fd = open(cmd->output->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				fprintf(stderr, "minishell: %s: No such file or directory\n", cmd->output->file);
				shell->exit_code = 1;
				return;
			}
			close(fd);
		}
		return;
	}
	if (is_builtin(cmd->argv[0]))
	{
		handle_builtin(cmd, shell);
	}
	else
	{
		exec_start(cmd, shell);
	}
}











int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	ft_init_shell(&shell, env);

	while (1)
	{
		shell.cmds = NULL;
		shell.tokens = NULL;

		if (isatty(fileno(stdin)))
			shell.input = readline("minishell> ");
		else
		{
			char *line = get_next_line(fileno(stdin));
			shell.input = ft_strtrim(line, "\n");
			free(line);
		}

		if (!shell.input)
			ft_exit(&shell);

		add_history(shell.input);
		shell.input = ft_expander(shell.input, &shell);

		if (ft_strcmp(shell.input, "") == 0)
		{
			free(shell.input);
			continue;
		}

		ft_lexer(shell.input, &shell.tokens);
		ft_parser(&shell, &shell.tokens);
		// print_command_details(shell.cmds);
		if (shell.cmds && shell.cmds->next == NULL)
			execute_single_command(shell.cmds, &shell);
		else
			exec_start(shell.cmds, &shell);

		free_command(shell.cmds);
		free_token_list(shell.tokens);
		free(shell.input);
		shell.input = NULL;
	}

	free_env_vars(shell.env_list);
	return (shell.exit_code);
}

// #define TESTER 1


// TO DO
// no expandir variables que se encuentren adentro de Q, quizas con un flag o algo

// unir tokens que con WORD DQ y Q que esten consecutivos

// checkear >">"


	// print_env_vars(shell.env_list);
// void handle_sigint(int sig)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	handle_sigquit(int sig)
// {

// }




		// print_command(shell.cmds);
// To do

// limpiar argv despues de conseguir input y output files

		// print_cmd_list(cmds);
		// print_linked_list(tokens);

// ver si puedo implementar una history
// ver que es expand

// 3.1.2.3 Double Quotes
// Enclosing characters in double quotes
// (‘"’) preserves the literal value of all characters
//  within the quotes, with the exception of ‘$’, ‘`’, ‘\’

// Tilde Expansion:

// Expands the tilde character (~) to the value of the home directory. For example, ~ expands to /home/username.
// Parameter and Variable Expansion:

// Replaces variables with their values. For example, $HOME expands to /home/username.
// Can also include modifiers, such as ${VAR:-default}, which provides a default value if the variable is unset.
