/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:14:12 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/05 17:35:16 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/parser.h"

// int	check_input_file(t_command **cmd)
// {
// 	int		i;

// 	i = 0;
// 	while ((*cmd)->argv[i] != NULL)
// 	{
// 		if (ft_strcmp((*cmd)->argv[i], "<") == 0
// 			|| ft_strcmp((*cmd)->argv[i], "<<") == 0)
// 		{
// 			if ((*cmd)->argv[i + 1] != NULL)
// 			{
// 				set_input_redirection(cmd, i);
// 				return (0);
// 			}
// 			else
// 			{
// 				printf("Error: Redir present and not output file \n");
// 				return (0);
// 			}
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// int	check_out_file(t_command **cmd)
// {
// 	int		i;

// 	i = 0;
// 	while ((*cmd)->argv[i] != NULL)
// 	{
// 		if (ft_strcmp((*cmd)->argv[i], ">") == 0
// 			|| ft_strcmp((*cmd)->argv[i], ">>") == 0)
// 		{
// 			if ((*cmd)->argv[i + 1] != NULL)
// 			{
// 				set_output_redirection(cmd, i);
// 				return (0);
// 			}
// 			else
// 			{
// 				printf("Error: Redir present and not output file \n");
// 				return (0);
// 			}
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// void	set_output_redirection(t_command **cmd, int i)
// {
// 	(*cmd)->output = malloc(sizeof(t_redirection));
// 	if (!(*cmd)->output)
// 		return ;
// 	if (ft_strcmp((*cmd)->argv[i], ">>") == 0)
// 		(*cmd)->output->type = REDIR_APPEND;
// 	else if (ft_strcmp((*cmd)->argv[i], ">") == 0)
// 		(*cmd)->output->type = REDIR_OUTPUT;
// 	(*cmd)->output->file = (*cmd)->argv[i + 1];
// }

// void	set_input_redirection(t_command **cmd, int i)
// {
// 	(*cmd)->output = malloc(sizeof(t_redirection));
// 	if (!(*cmd)->output)
// 		return ;
// 	if (ft_strcmp((*cmd)->argv[i], "<<") == 0)
// 		(*cmd)->output->type = REDIR_HEREDOC;
// 	else if (ft_strcmp((*cmd)->argv[i], "<") == 0)
// 		(*cmd)->output->type = REDIR_INPUT;
// 	(*cmd)->output->file = (*cmd)->argv[i + 1];
// }
