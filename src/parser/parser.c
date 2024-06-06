/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:31:19 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/05 17:35:19 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/parser.h"
// #include <stdio.h>

// void	free_tarray(char ***tarray)
// {
// 	char	***ptr;
// 	char	**inner_ptr;

// 	if (tarray == NULL)
// 		return ;
// 	ptr = tarray;
// 	while (*ptr != NULL)
// 	{
// 		inner_ptr = *ptr;
// 		while (*inner_ptr != NULL)
// 		{
// 			free(*inner_ptr);
// 			inner_ptr++;
// 		}
// 		free(*ptr);
// 		ptr++;
// 	}
// 	free(tarray);
// }

// void	ft_print_cmds(char ***cmds)
// {
// 	int i, j;

// 	i = 0;
// 	while (cmds[i] != NULL)
// 	{
// 		printf("Command %d: ", i + 1);
// 		j = 0;
// 		while (cmds[i][j] != NULL)
// 		{
// 			printf("[%d]\"%s\" ", j, cmds[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

// void	ft_parser(t_token **tokens, t_command *cmds)
// {
// 	char	***tarray;

// 	tarray = ft_tarray(tokens);
// 	ft_pop_struct(&cmds, tarray);
// 	free_tarray(tarray);
// }
