/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:36:57 by mvolkman          #+#    #+#             */
/*   Updated: 2024/06/21 09:54:23 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"



// Updates the PWD and OLDPWD environment variables
void	update_pwd(t_env_var **env_list, char *old_pwd)
{
	char	buffer[1024];
	char	*new_pwd;

	// Get the current working directory and store it in buffer
	new_pwd = getcwd(buffer, sizeof(buffer));
	if (!new_pwd) // Check if getcwd failed
	{
		perror("getcwd"); // Print error message
		return ; // Exit the function if there's an error
	}
	// Update the OLDPWD environment variable to the old_pwd value
	update_env_var(env_list, "OLDPWD", old_pwd);
	// Update the PWD environment variable to the new_pwd value
	update_env_var(env_list, "PWD", new_pwd);
}

// Changes the directory to the home directory
void	change_to_home(t_env_var **env_list)
{
	char	*home_dir;

	// Retrieve the value of the HOME environment variable
	home_dir = get_env_value(*env_list, "HOME");
	if (!home_dir) // Check if HOME is not set
	{
		fprintf(stderr, "cd: HOME not set\n"); // Print error message
		return ; // Exit the function if HOME is not set
	}
	// Change directory to the home directory
	if (chdir(home_dir) != 0)
	{
		perror("chdir"); // Print error message if chdir fails
	}
}

// Changes the current working directory
void	ft_cd(char **args, t_env_var **env_list)
{
	char	buffer[1024];
	char	*old_pwd;

	// Get the current working directory and store it in buffer
	old_pwd = getcwd(buffer, sizeof(buffer));
	if (!old_pwd) // Check if getcwd failed
	{
		perror("getcwd"); // Print error message
		return ; // Exit the function if there's an error
	}

	// Check if no argument is given or the argument is '~'
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		// Change directory to the home directory
		change_to_home(env_list);
	}
	else if (chdir(args[1]) != 0) // Attempt to change directory to the given path
	{
		perror("chdir"); // Print error message if chdir fails
		return ; // Exit the function if there's an error
	}

	// Update the PWD and OLDPWD environment variables
	update_pwd(env_list, old_pwd);
}

// void	update_pwd(t_env_var **env_list, char *old_pwd)
// {
// 	char	buffer[1024];
// 	char	*new_pwd;

// 	new_pwd = getcwd(buffer, sizeof(buffer));
// 	if (!new_pwd)
// 	{
// 		perror("getcwd");
// 		return ;
// 	}
// 	update_env_var(env_list, "OLDPWD", old_pwd);
// 	update_env_var(env_list, "PWD", new_pwd);
// }

// void	change_to_home(t_env_var **env_list)
// {
// 	char	*home_dir;

// 	home_dir = get_env_value(*env_list, "HOME");
// 	if (!home_dir)
// 	{
// 		fprintf(stderr, "cd: HOME not set\n");
// 		return ;
// 	}
// 	if (chdir(home_dir) != 0)
// 	{
// 		perror("chdir");
// 	}
// }

// void	ft_cd(char **args, t_env_var **env_list)
// {
// 	char	buffer[1024];
// 	char	*old_pwd;

// 	old_pwd = getcwd(buffer, sizeof(buffer));
// 	if (!old_pwd)
// 	{
// 		perror("getcwd");
// 		return ;
// 	}
// 	if (!args[1] || ft_strcmp(args[1], "~") == 0)
// 	{
// 		change_to_home(env_list);
// 	}
// 	else if (chdir(args[1]) != 0)
// 	{
// 		perror("chdir");
// 		return ;
// 	}
// 	update_pwd(env_list, old_pwd);
// }
