/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:09:54 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/26 10:51:24 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ignore_sigint(struct sigaction *old_action)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, old_action);
}

void	restore_sigint(const struct sigaction *old_action)
{
	sigaction(SIGINT, old_action, NULL);
}

void	ft_restore_terminal(int i)
{
	static struct termios	original_term_settings;

	if (!i)
		tcgetattr(STDIN_FILENO, &original_term_settings);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &original_term_settings);
}
