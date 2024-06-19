#include "../../../includes/builtins.h"

void ft_echo(char **args, t_env_var *env_list)
{
	int i;
	int newline;
	char *env_value;

	newline = 1;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			env_value = get_env_value(env_list, args[i] + 1);
			if (env_value)
				ft_putstr_fd(env_value, STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd(args[i], STDOUT_FILENO);
		}
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
