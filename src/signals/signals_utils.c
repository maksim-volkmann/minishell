/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:09:54 by mvolkman          #+#    #+#             */
/*   Updated: 2024/07/24 16:13:03 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_restore_terminal(int i)
{
	static struct termios	original_term_settings;

	if (!i)
		tcgetattr(STDIN_FILENO, &original_term_settings);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &original_term_settings);
}
