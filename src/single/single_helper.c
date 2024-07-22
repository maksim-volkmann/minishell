/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:00:30 by goldman           #+#    #+#             */
/*   Updated: 2024/07/22 12:06:06 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	file_err(const char *file, t_shell *shell)
{
	prnt_err(file, "No such file or directory", 1, shell);
	return (1);
}

int	is_builtin(char *command)
{
	return (
		ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "exit") == 0
		|| ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "unset") == 0
		|| ft_strcmp(command, "env") == 0
	);
}
