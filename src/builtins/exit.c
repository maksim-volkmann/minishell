/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:53:27 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/25 08:29:22 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int	count_args(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

bool	is_valid_number(char *arg)
{
	int		i;
	bool	has_sign;

	i = 0;
	has_sign = false;
	while (arg[i])
	{
		if ((!ft_isdigit(arg[i]) && arg[i] != '-' && arg[i] != '+')
			|| (has_sign && (arg[i] == '-' || arg[i] == '+')))
			return (false);
		if (arg[i] == '-' || arg[i] == '+')
			has_sign = true;
		i++;
	}
	return (true);
}

int	execute_exit(char **argv, t_shell *shell)
{
	int	count;

	count = count_args(argv);
	if (count == 1)
		ft_exit(shell);
	if (ft_strcmp(argv[1], "") == 0 || !is_valid_number(argv[1]))
	{
		shell->exit_code = 255;
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		ft_exit(shell);
	}
	if (count == 2)
	{
		shell->exit_code = ft_atoi(argv[1]);
		ft_exit(shell);
	}
	ft_putendl_fd("exit\nminishell: exit: too many arguments", STDERR_FILENO);
	shell->exit_code = 1;
	return (1);
}
