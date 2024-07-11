/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/11 13:51:03 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include <sys/fcntl.h>

char *ft_expander_hd(char *input, t_shell *shell)
{
	char *exp_input;
	int i;

	exp_input = ft_strdup("");
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			exp_input = ft_handle_single_quote(input, &i , exp_input);
		else if (input[i] == '\"')
			exp_input = ft_handle_double_quote(input, &i, shell, exp_input);
		else
			exp_input = ft_handle_segment(input, &i, shell, exp_input);
	}

	free(input);
	return exp_input;
}
