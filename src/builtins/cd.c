/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:15:51 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/24 11:54:32 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int	change_to_home(t_env **env_list)
{
	char	*home_dir;

	home_dir = get_env_value(*env_list, "HOME");
	if (!home_dir)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (1);
	}
	if (chdir(home_dir) != 0)
	{
		perror("chdir");
		return (1);
	}
	return (0);
}

int	execute_cd(char **args, t_env **env_list)
{
	char	buffer[1024];
	char	*old_pwd;
	int		status;

	old_pwd = getcwd(buffer, sizeof(buffer));
	if (!old_pwd)
	{
		perror("getcwd");
		return (1);
	}
	if (!args[1])
	{
		if (change_to_home(env_list) != 0)
			return (1);
		status = update_pwd(env_list, old_pwd);
		return (status);
	}
	if (chdir(args[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (1);
	}
	status = update_pwd(env_list, old_pwd);
	return (status);
}
