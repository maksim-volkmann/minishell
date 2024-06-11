/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:17:35 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/11 11:55:11 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

// extern int rl_replace_line(const char *text, int clear_undo);

// void	leaks(void)
// {
// 	system("leaks minishell_2");
// }
// atexit(leaks);

const char* get_token_type_string(t_token_type type) {
    switch (type) {
        case LESS:    return "LESS";
        case GREAT:   return "GREAT";
        case PIPE:    return "PIPE";
        case LPAR:    return "LPAR";
        case RPAR:    return "RPAR";
        case WORD:    return "WORD";
        // case QUOTE:   return "QUOTE";
        // case DQUOTE:  return "DQUOTE";
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

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_token		*tokens;
	t_command	*cmds;

	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		cmds = NULL;
		tokens = NULL;
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			continue ;
		}
		ft_lexer(input, &tokens);
		print_token_list(tokens);
		ft_parser(&cmds, &tokens);
		// execute_commands(cmds, env);
		free_command(cmds);
		free_token_list(tokens);
		free(input);
	}
	return (0);
}

		// print_command(cmds);
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
