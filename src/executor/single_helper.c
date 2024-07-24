/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:57:33 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/24 18:39:46 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void	prnt_err(const char *cmd, const char *msg, int code, t_shell *shell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	shell->exit_code = code;
}

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
