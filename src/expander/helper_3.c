/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:23:35 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/08 12:52:35 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
char *ft_handle_single_quote(char *input, int *index, char *exp_input)
{
	char *temp;
	char *new_exp_input;

	temp = ft_extract_sq(input, index);
	new_exp_input = ft_join_input(exp_input, temp);
	free(temp);
	return new_exp_input;
}

char *ft_handle_double_quote(char *input, int *index, t_shell *shell, char *exp_input)
{
	char *temp;
	char *new_exp_input;

	temp = ft_extract_dq(input, index, shell);
	new_exp_input = ft_join_input(exp_input, temp);
	free(temp);
	return new_exp_input;
}

char *ft_handle_segment(char *input, int *index, t_shell *shell, char *exp_input)
{
	char *temp;
	char *new_exp_input;

	temp = ft_extract_segment(input, index, shell);
	new_exp_input = ft_join_input(exp_input, temp);
	return new_exp_input;
}

int	ft_is_separator_var(char c)
{
	int	i;

	i = 0;
	while (NOVAR[i] != '\0')
	{
		if (NOVAR[i] == c)
			return (1);
		i++;
	}
	return (0);
}