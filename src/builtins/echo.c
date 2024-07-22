#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>


// Function to update an environment variable
// This function updates the value of an environment variable or adds it if it doesn't exist
void	update_env_var(t_env **env_list, const char *key, const char *value)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	add_env_var(env_list, key, value);
}

// Function to update the PWD and OLDPWD environment variables
// This function updates the current and previous working directories
int	update_pwd(t_env **env_list, char *old_pwd)
{
	char	buffer[1024];
	char	*new_pwd;

	new_pwd = getcwd(buffer, sizeof(buffer));
	if (!new_pwd)
	{
		perror("getcwd");
		return (1);
	}
	update_env_var(env_list, "OLDPWD", old_pwd);
	update_env_var(env_list, "PWD", new_pwd);
	return (0);
}


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
