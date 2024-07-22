#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

// Function to print export variables
void	print_export_vars(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

// Function to reduce white space in a string
void	reduce_white_space(char *str)
{
	char	*dst;
	char	*src;
	int		in_word;

	dst = str;
	src = str;
	in_word = 0;
	while (ft_isspace((unsigned char)*src))
		src++;
	while (*src)
	{
		if (ft_isspace((unsigned char)*src))
		{
			if (in_word)
			{
				*dst++ = ' ';
				in_word = 0;
			}
		}
		else
		{
			*dst++ = *src;
			in_word = 1;
		}
		src++;
	}
	if (dst > str && ft_isspace((unsigned char)*(dst - 1)))
		dst--;
	*dst = '\0';
}

// Function to check if a variable name is valid
int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// Function to find the += operator in a string
char	*find_plus_equal(const char *str)
{
	return (ft_strnstr(str, "+=", ft_strlen(str)));
}

// Function to handle adding or updating an environment variable with concatenation
void	handle_plus_equal(char *arg, t_env **env_list, t_shell *shell)
{
	char	*plus_equal_sign;
	char	*key;
	char	*value;
	t_env	*current;

	plus_equal_sign = find_plus_equal(arg);
	*plus_equal_sign = '\0';
	key = arg;
	value = plus_equal_sign + 2;
	if (is_valid_var_name(key))
	{
		current = *env_list;
		while (current)
		{
			if (ft_strcmp(current->key, key) == 0)
			{
				char *new_value = ft_strjoin(current->value, value);
				free(current->value);
				current->value = new_value;
				return;
			}
			current = current->next;
		}
		add_env_var(env_list, key, value);
	}
	else
	{
		*plus_equal_sign = '+';
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		shell->exit_code = 1;
	}
}

// Function to handle adding or updating an environment variable
void	handle_equal_sign(char *arg, t_env **env_list, t_shell *shell)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	*equal_sign = '\0';
	key = arg;
	value = equal_sign + 1;
	if (is_valid_var_name(key))
		update_env_var(env_list, key, value);
	else
	{
		*equal_sign = '=';
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		shell->exit_code = 1;
	}
}

// Function to handle adding an environment variable without a value
void	handle_no_equal_sign(char *arg, t_env **env_list, t_shell *shell)
{
	if (is_valid_var_name(arg))
		update_env_var(env_list, arg, NULL);
	else
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		shell->exit_code = 1;
	}
}

// Function to handle each export argument
void	handle_export_arg(char *arg, t_env **env_list, t_shell *shell)
{
	if (find_plus_equal(arg) != NULL)
		handle_plus_equal(arg, env_list, shell);
	else if (ft_strchr(arg, '=') != NULL)
		handle_equal_sign(arg, env_list, shell);
	else
		handle_no_equal_sign(arg, env_list, shell);
}

// Function to handle the export command
void	execute_export(char **args, t_env **env_list, t_shell *shell)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
		print_export_vars(*env_list);
	else
	{
		while (args[i])
		{
			handle_export_arg(args[i], env_list, shell);
			i++;
		}
	}
	if (shell->exit_code == 0)
		shell->exit_code = 0;
}
