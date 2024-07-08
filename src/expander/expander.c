/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/08 12:53:06 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include <sys/fcntl.h>

char	*ft_extract_sq(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	start = (*i);
	(*i)++;
	while (input[(*i)] != 0 && input[(*i)] != '\'')
		(*i)++;
	if (input[*i] == '\'' && input[(*i) + 1] != 0)
		(*i)++;
	end = (*i);
	segment = ft_extract_str(input, start, end);
	return (segment);
}


char	*ft_extract_dq(char *input, int *i, t_shell *shell)
{
	char	*segment;
	char	*exp_var;
	char	*temp_segment;

	segment = strdup("");
	if (!segment)
		return (NULL);
	(*i)++;
	while (input[*i] != '\0' && input[*i] != '\"')
	{
		temp_segment = ft_extract_segment_dq(input, i);
		if (temp_segment)
		{
			segment = ft_join_input(segment, temp_segment);
			free(temp_segment);
		}
		if (input[*i] == '$')
		{
			exp_var = ft_extract_var(input, i);
			if (exp_var)
			{
				exp_var = ft_expand_var_dq(shell, exp_var);
				if (exp_var)
					segment = ft_join_input(segment, exp_var);
				free(exp_var);
			}
		}
	}
	if (input[*i] == '\"')
		(*i)++;
	segment = ft_quote_string(segment);
	return (segment);
}

char	*ft_extract_segment(char *input, int *i, t_shell *shell)
{
	char	*segment;
	char	*exp_var;
	char	*temp_segment;

	segment = strdup("");
	if (!segment)
		return (NULL);
	while (input[*i] != '\0' && input[*i] != '\"' && input[*i] != '\'')
	{
		temp_segment = ft_segment_helper(input, i);
		if (temp_segment)
		{
			segment = ft_join_input(segment, temp_segment);
			free(temp_segment);
		}
		if (input[*i] == '$')
		{
			exp_var = ft_extract_var(input, i);
			if (exp_var)
			{
				exp_var = ft_expand_var(shell, exp_var);
				if (exp_var)
					segment = ft_join_input(segment, exp_var);
				free(exp_var);
			}
		}
	}
	return (segment);
}

char *ft_expander(char *input, t_shell *shell)
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

// char	*ft_expander(char *input, t_shell *shell)
// {
// 	char	*exp_input;
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	exp_input = ft_strdup("");
// 	while (input[i] != 0)
// 	{
// 		if (input[i] == '\'')
// 		{
// 			temp = ft_extract_sq(input, &i);
// 			exp_input = ft_join_input(exp_input, temp);
// 			free(temp);
// 		}
// 		else if (input[i] == '\"')
// 		{
// 			temp = ft_extract_dq(input, &i, shell);
// 			exp_input = ft_join_input(exp_input, temp);
// 			free(temp);
// 		}
// 		else
// 		{
// 			temp = ft_extract_segment(input, &i, shell);
// 			exp_input = ft_join_input(exp_input, temp);
// 			free(temp);
// 		}
// 	}
// 	free(input);
// 	return (exp_input);
// }
