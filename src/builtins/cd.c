/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:15:51 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/23 12:16:04 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

// Function to change the directory to the home directory
// This function changes the current working
// directory to the user's home directory

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
