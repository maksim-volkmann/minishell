/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:00:30 by mvolkman           #+#    #+#             */
/*   Updated: 2024/07/23 12:31:41 by adrherna         ###   ########.fr       */
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
