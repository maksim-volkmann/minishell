/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/22 10:03:15 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/heredoc.h"
#include <sys/fcntl.h>

// char	*ft_handle_double_quote_hd(char *input, int *index,
// 		t_shell *shell, char *exp_input)
// {
// 	char	*temp;
// 	char	*new_exp_input;

// 	temp = ft_extract_dq_hd(input, index, shell);
// 	// temp = ft_quote_string(temp);
// 	new_exp_input = ft_join_input(exp_input, temp);
// 	free(temp);
// 	return (new_exp_input);
// }

char	*ft_expander_hd(char *input, t_shell *shell)
{
	char	*exp_input;
	int		i;

	exp_input = ft_strdup("");
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			exp_input = ft_handle_single_quote(input, &i, exp_input);
		else if (input[i] == '\"')
			exp_input = ft_handle_double_quote_hd(input, &i, shell, exp_input);
		else
			exp_input = ft_handle_segment(input, &i, shell, exp_input);
	}
	free(input);
	return (exp_input);
}
