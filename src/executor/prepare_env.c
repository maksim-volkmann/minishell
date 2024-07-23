/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:38:21 by goldman           #+#    #+#             */
/*   Updated: 2024/07/23 12:24:48 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# include <unistd.h>
#include <fcntl.h>
#include "../../includes/executor.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	count_envs(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

char	*create_env_var_string(const char *key, const char *value)
{
	char	*env_var;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	env_var = malloc(key_len + value_len + 2);
	if (!env_var)
		return (NULL);
	ft_strcpy(env_var, key);
	env_var[key_len] = '=';
	ft_strcpy(env_var + key_len + 1, value);
	return (env_var);
}

void	free_envp_on_error(char **envp, int i)
{
	while (i > 0)
		free(envp[--i]);
	free(envp);
}

char	**prepare_envp(t_env *env_list)
{
	char		**envp;
	int			env_count;
	int			i;
	t_env		*current;

	env_count = count_envs(env_list);
	envp = malloc(sizeof(char *) * (env_count + 1));
	if (!envp)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		envp[i] = create_env_var_string(current->key, current->value);
		if (!envp[i])
		{
			free_envp_on_error(envp, i);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp[env_count] = NULL;
	return (envp);
}



