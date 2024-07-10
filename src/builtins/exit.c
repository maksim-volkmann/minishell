#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

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
	int	i;
	bool	has_sign;

	i = 0;
	has_sign = false;
	while (arg[i])
	{
		if ((!ft_isdigit(arg[i]) && arg[i] != '-' && arg[i] != '+') ||
			(has_sign && (arg[i] == '-' || arg[i] == '+')))
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
		fprintf(stderr, "exit\nminishell: exit: %s: numeric argument required\n", argv[1]);
		ft_exit(shell);
	}
	if (count == 2)
	{
		shell->exit_code = ft_atoi(argv[1]);
		ft_exit(shell);
	}
	fprintf(stderr, "exit\nminishell: exit: too many arguments\n");
	shell->exit_code = 1;
	return (1);
}


