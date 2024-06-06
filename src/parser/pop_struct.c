/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:51:31 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/05 17:35:22 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>

// void	print_redirection(const char *prefix, t_redirection *redir)
// {
//     if (redir == NULL)
//     {
//         printf("%s: None\n", prefix);
//         return;
//     }

//     printf("%s: ", prefix);
//     switch (redir->type)
//     {
//         case REDIR_INPUT:
//             printf("Input, File: %s\n", redir->file);
//             break;
//         case REDIR_OUTPUT:
//             printf("Output, File: %s\n", redir->file);
//             break;
//         case REDIR_APPEND:
//             printf("Append, File: %s\n", redir->file);
//             break;
//         case REDIR_HEREDOC:
//             printf("Heredoc, File: %s\n", redir->file);
//             break;
//         default:
//             printf("None\n");
//             break;
//     }
// }

// void	print_command(t_command *cmd)
// {
//     while (cmd != NULL)
//     {
//         printf("Arguments:\n");
//         for (int i = 0; cmd->argv[i] != NULL; i++)
//         {
//             printf("  argv[%d]: %s\n", i, cmd->argv[i]);
//         }
//         print_redirection("Output Redirection", cmd->output);
//         printf("Next command: %s\n", cmd->next ? "Present" : "None");
//         cmd = cmd->next;
//     }
// }

// void	ft_check_in_out(t_command **cmd)
// {
// 	int	has_input_redir;
// 	int	has_output_redir;

// 	has_input_redir = check_input_file(cmd);
// 	has_output_redir = check_out_file(cmd);
// 	if (has_input_redir == 1 && has_output_redir == 1)
// 	{
// 		(*cmd)->output = malloc(sizeof(t_redirection));
// 		if (!(*cmd)->output)
// 			return ;
// 		(*cmd)->output->type = REDIR_NONE;
// 	}
// }

// void	ft_pop_struct(t_command **cmds, char ***tarray)
// {
// 	t_command	*new;
// 	t_command	*current;
// 	int			i;

// 	i = 0;
// 	while (tarray[i] != NULL)
// 	{
// 		new = ft_new_node(tarray[i]);
// 		if (!new)
// 		{
// 			printf("Error: Could not allocate new command node\n");
// 			return ;
// 		}
// 		add_or_init_node(cmds, new);
// 		current = new;
// 		ft_check_in_out(&current);
// 		print_command(*cmds);
// 		i++;
// 	}

// }
