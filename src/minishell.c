
#include "../includes/executor.h"
#include <stdio.h>

// extern int rl_replace_line(const char *text, int clear_undo);

void	leaks(void)
{
	system("leaks minishell");
}

void free_env_vars(t_env_var *env_list)
{
    t_env_var *current;
    t_env_var *next;

    current = env_list;
    while (current != NULL) {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}

const char* get_token_type_string(t_token_type type) {
    switch (type) {
        case LESS:    return "LESS";
        case GREAT:   return "GREAT";
        case PIPE:    return "PIPE";
        case LPAR:    return "LPAR";
        case RPAR:    return "RPAR";
        case WORD:    return "WORD";
        case QUOTE:   return "QUOTE";
        case DQUOTE:  return "DQUOTE";
        case DLESS:   return "DLESS";
        case DGREAT:  return "DGREAT";
        case AND:     return "AND";
        case DAND:    return "DAND";
        case NUM:     return "NUM";
        case SPACES:  return "SPACES";
        default:      return "UNKNOWN";
    }
}

// Function to print the linked list
void print_token_list(t_token *head) {
    t_token *current = head;

    while (current != NULL) {
        printf("Token: |%s|, Type: %s\n", current->token, get_token_type_string(current->type));
        current = current->next;
    }
}

const char* redir_type_to_string(t_redir_type type) {
    switch (type) {
        case REDIR_NONE: return "REDIR_NONE";
        case REDIR_INPUT: return "REDIR_INPUT";
        case REDIR_OUTPUT: return "REDIR_OUTPUT";
        case REDIR_APPEND: return "REDIR_APPEND";
        case REDIR_HEREDOC: return "REDIR_HEREDOC";
        default: return "UNKNOWN";
    }
}

void print_redirection(t_redirection *redir) {
    if (redir != NULL) {
        printf("  Redirection Type: %s\n", redir_type_to_string(redir->type));
        if (redir->file != NULL) {
            printf("  Redirection File: %s\n", redir->file);
        } else {
            printf("  Redirection File: NULL\n");
        }
    } else {
        printf("  Redirection: NULL\n");
    }
}

void print_command(t_command *cmd) {
    int i;
    while (cmd != NULL) {
        printf("Command:\n");

        if (cmd->argv != NULL) {
            printf("  Arguments: ");
            for (i = 0; cmd->argv[i] != NULL; i++) {
                printf("|%s|", cmd->argv[i]);
            }
            printf("\n");
        } else {
            printf("  Arguments: NULL\n");
        }

        printf("Input:\n");
        print_redirection(cmd->input);

        printf("Output:\n");
        print_redirection(cmd->output);

        cmd = cmd->next;

        printf("\n");
    }
}

void copy_env_vars(t_shell *shell, char **env)
{
    int        i;
    char    *key;
    char    *value;
    char    *sep;

    i = 0;
    while (env[i])
    {
        sep = ft_strchr(env[i], '=');
        if (!sep)
        {
            i++;
            continue;
        }
        key = ft_substr(env[i], 0, sep - env[i]);
        value = ft_strdup(sep + 1);
        add_env_var(&shell->env_list, key, value);
        free(key);
        free(value);
        i++;
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

        current_cmd = current_cmd->next;
    }
}

int main(int argc, char **argv, char **env)
{
	char        *input;
	t_token     *tokens;
	t_shell     shell;

	// atexit(leaks);
	shell.env_list = NULL;
	copy_env_vars(&shell, env);
	shell.exit_code = 0;
	while (1)
	{
		shell.cmds = NULL;
		tokens = NULL;

		if (isatty(fileno(stdin)))
			input = readline("minishell> ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		// input = readline("minishell> ");
		if (!input)
			exit(0);
        add_history(input);
        // printf("%s\n", input);
		input = ft_expander(input, shell.env_list);
		printf("%s\n", input);
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			break ;
		}
		ft_lexer(input, &tokens);
		print_token_list(tokens);
		ft_parser(&shell.cmds, &tokens);
		// PRINTING SHELL STRUCT!!!
		// print_command_details(shell.cmds);
		// EXECUTION
		if (is_builtin(shell.cmds->argv[0]))
		{
			execute_builtin(shell.cmds, &shell.env_list);
		}
		else
		{
			execute_commands(shell.cmds, shell.env_list);
		}
		free_command(shell.cmds);
		free_token_list(tokens);
		free(input);
	}
	free_env_vars(shell.env_list);
	return (0);
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
