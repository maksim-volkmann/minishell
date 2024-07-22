/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:21:29 by goldman           #+#    #+#             */
/*   Updated: 2024/07/22 12:43:53 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

char	*create_cmd_path(char *dir, char *cmd)
{
	char	*path;
	char	*full_path;

	path = ft_strjoin(dir, "/");
	full_path = ft_strjoin(path, cmd);
	free(path);
	return (full_path);
}

char	*get_env_value(t_env_var *env_list, const char *key)
{
	t_env_var	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*find_correct_path(char *cmd, t_env_var *env_list)
{
	char	*path_var;
	char	**paths;
	char	*correct_path;
	int		i;

	path_var = get_env_value(env_list, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	i = 0;
	while (paths[i])
	{
		correct_path = create_cmd_path(paths[i], cmd);
		if (access(correct_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (correct_path);
		}
		free(correct_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	*get_executable_path(char *cmd, t_env_var *env_list)
{
	char	*executable_path;

	if (ft_strchr(cmd, '/') != NULL)
		executable_path = ft_strdup(cmd);
	else
	{
		executable_path = find_correct_path(cmd, env_list);
		if (executable_path == NULL)
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			exit(127);
		}
	}
	return (executable_path);
}

void	execute_command(t_command *cmd, t_env_var *env_list)
{
	char	*executable_path;
	char	**envp;

	executable_path = get_executable_path(cmd->argv[0], env_list);
	envp = prepare_envp(env_list);
	execve(executable_path, cmd->argv, envp);
	free_envp(envp);
	perror("execve failed");
	free(executable_path);
	exit(EXIT_FAILURE);
}
