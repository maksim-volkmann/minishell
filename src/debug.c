/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:02:01 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/26 10:02:08 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

// char* get_token_type_string(t_token_type type)
// {
//     switch (type) {
//         case LESS:    return "LESS";
//         case GREAT:   return "GREAT";
//         case PIPE:    return "PIPE";
//         case LPAR:    return "LPAR";
//         case RPAR:    return "RPAR";
//         case WORD:    return "WORD";
//         case QUOTE:   return "QUOTE";
//         case DQUOTE:  return "DQUOTE";
//         case DLESS:   return "DLESS";
//         case DGREAT:  return "DGREAT";
//         case AND:     return "AND";
//         case DAND:    return "DAND";
//         case NUM:     return "NUM";
//         case SPACES:  return "SPACES";
//         default:      return "UNKNOWN";
//     }
// }

// // Function to print the linked list
// void print_token_list(t_token *head)
// {
//     t_token *current = head;

//     while (current != NULL) {
//         printf("Token: |%s|, Type: %s\n", current->token,
// get_token_type_string(current->type));
//         current = current->next;
//     }
// }

// char* redir_type_to_string(t_redir_type type)
// {
//     switch (type) {
//         case REDIR_NONE: return "REDIR_NONE";
//         case REDIR_INPUT: return "REDIR_INPUT";
//         case REDIR_OUTPUT: return "REDIR_OUTPUT";
//         case REDIR_APPEND: return "REDIR_APPEND";
//         case REDIR_HEREDOC: return "REDIR_HEREDOC";
//         default: return "UNKNOWN";
//     }
// }

// void print_redir(t_redir *redir)
// {
//     if (redir != NULL) {
//         printf("  Redirection Type: %s\n",
// redir_type_to_string(redir->type));
//         if (redir->file != NULL) {
//             printf("  Redirection File: %s\n", redir->file);
//         } else {
//             printf("  Redirection File: NULL\n");
//         }
//     } else {
//         printf("  Redirection: NULL\n");
//     }
// }

// void print_cmd(t_cmd *cmd)
// {
//     int i;
//     while (cmd != NULL) {
//         printf("Command:\n");

//         if (cmd->argv != NULL) {
//             printf("  Arguments: ");
//             for (i = 0; cmd->argv[i] != NULL; i++) {
//                 printf("|%s|", cmd->argv[i]);
//             }
//             printf("\n");
//         } else {
//             printf("  Arguments: NULL\n");
//         }

//         printf("Input:\n");
//         print_redir(cmd->input);

//         printf("Output:\n");
//         print_redir(cmd->output);

//         cmd = cmd->next;

//         printf("\n");
//     }
// }

// void print_cmd_details(t_cmd *cmds)
// {
//     t_cmd *current_cmd = cmds;
//     int i;

//     while (current_cmd)
//     {
//         printf("Command:\n");

//         // Print all arguments
//         for (i = 0; current_cmd->argv[i]; i++)
//         {
//             printf("  Arg[%d]: %s\n", i, current_cmd->argv[i]);
//         }

//         // Print input redirection details if present
//         if (current_cmd->input)
//         {
//             printf("  Input Redirection:\n");
//             printf("    Type: %d\n", current_cmd->input->type);
//             printf("    File: %s\n", current_cmd->input->file);
//         }
//         else
//         {
//             printf("  Input Redirection: None\n");
//         }

//         // Print output redirection details if present
//         if (current_cmd->output)
//         {
//             printf("  Output Redirection:\n");
//             printf("    Type: %d\n", current_cmd->output->type);
//             printf("    File: %s\n", current_cmd->output->file);
//         }
//         else
//         {
//             printf("  Output Redirection: None\n");
//         }

//         // Print next command details if present
//         if (current_cmd->next)
//         {
//             printf("  Next Command:\n");
//             for (int j = 0; current_cmd->next->argv[j]; j++)
//             {
//                 printf("Next Arg[%d]: %s\n", j, current_cmd->next->argv[j]);
//             }
//         }
//         else
//         {
//             printf("  Next Command: None\n");
//         }

//         current_cmd = current_cmd->next;
//     }
// }