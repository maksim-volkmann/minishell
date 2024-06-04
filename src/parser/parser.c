/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:31:19 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/04 09:47:09 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdio.h>

void	ft_print_cmds(char ***cmds)
{
	int i, j;

	i = 0;
	while (cmds[i] != NULL)
	{
		printf("Command %d: ", i + 1);
		j = 0;
		while (cmds[i][j] != NULL)
		{
			printf("[%d]\"%s\" ", j, cmds[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_parser(t_token **tokens, t_command *cmds)
{
	char	***tarray;

	ft_tarray(tokens, tarray);
}
