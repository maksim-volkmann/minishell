/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:33:59 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/30 16:46:41 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "../includes/lexer.h"

typedef struct s_cmd
{
	char			**cmd;
	char			*output;
	struct s_cmd	*next;
}	t_cmd;

// parser.c

void	ft_parser(t_token **tokens, char ***cmds);
char	***ft_cmds_malloc(t_token	**tokens);
void	ft_extract_cmd(t_token **tokens, char ***cmds);
void	ft_fill_array(t_token **tokens, char ***cmds);
void	ft_print_cmds(char ***cmds);

#endif