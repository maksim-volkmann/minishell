/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/14 13:05:52 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include <sys/fcntl.h>

char	*ft_extract_segment(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	start = (*i);
	while (input[(*i)] != 0 && input[(*i)] != '$')
		(*i)++;
	end = (*i);
	segment = ft_extract_str(input, start, end);
	return (segment);
}

char	*ft_expander(char *input, t_env_var *env)
{
	char	*exp_input;
	char	*exp_var;
	char	*temp;
	int		i;

	i = 0;
	exp_input = ft_strdup("");
	while (input[i] != 0)
	{
		if (input[i] == '$')
		{
			exp_var = ft_extract_var(input, &i);
			exp_var = ft_expand_var(env, exp_var);
			exp_input = ft_join_input(exp_input, exp_var);
		}
		else
		{
			temp = ft_extract_segment(input, &i);
			exp_input = ft_join_input(exp_input, temp);
			free(temp);
		}
	}
	free(input);
	return (exp_input);
}

			// exp_var = ft_extract_var(input, &i);
			// exp_var = ft_expand_var(env, exp_var);
			// temp = ft_strjoin(exp_input, exp_var);
			// free(exp_input);
			// exp_input = temp;

			// exp_var = ft_extract_var(input, &i);
			// exp_var = ft_expand_var(env, exp_var);
			// exp_input = ft_join_input(exp_input, exp_var);


// hola $USER