/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:16:25 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/24 20:31:04 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

bool	check_newline_flag(char **argv, int *i)
{
	int		j;
	bool	newline;

	newline = true;
	while (argv[*i] && ft_strncmp(argv[*i], "-n", 2) == 0)
	{
		j = 2;
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] == '\0')
			newline = false;
		else
			break ;
		(*i)++;
	}
	return (newline);
}

void	execute_echo(char **argv)
{
	int		i;
	bool	newline;

	i = 1;
	newline = check_newline_flag(argv, &i);
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
