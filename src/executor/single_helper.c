/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:57:33 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/24 13:49:43 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
