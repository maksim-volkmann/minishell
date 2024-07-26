/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:07:54 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/26 10:52:54 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	free_env_vars(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

t_env	*create_env_var(const char *key, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_var->key = ft_strdup(key);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	new_var->next = NULL;
	return (new_var);
}

void	add_env_var(t_env **env_list, const char *key, const char *value)
{
	t_env	*new_var;
	t_env	*current;
	t_env	*prev;

	new_var = create_env_var(key, value);
	prev = NULL;
	if (*env_list == NULL || ft_strcmp((*env_list)->key, key) > 0)
	{
		new_var->next = *env_list;
		*env_list = new_var;
	}
	else
	{
		current = *env_list;
		while (current != NULL && ft_strcmp(current->key, key) < 0)
		{
			prev = current;
			current = current->next;
		}
		new_var->next = current;
		if (prev)
			prev->next = new_var;
	}
}

void	copy_env_vars(t_shell *shell, char **env)
{
	int		i;
	char	*key;
	char	*value;
	char	*sep;

	i = 0;
	while (env[i])
	{
		sep = ft_strchr(env[i], '=');
		if (!sep)
		{
			i++;
			continue ;
		}
		key = ft_substr(env[i], 0, sep - env[i]);
		value = ft_strdup(sep + 1);
		add_env_var(&shell->env_list, key, value);
		free(key);
		free(value);
		i++;
	}
}
