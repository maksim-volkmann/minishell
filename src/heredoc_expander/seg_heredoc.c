/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:57:08 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/25 17:33:02 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/heredoc.h"

char	*ft_handle_segment_hd(char *input, int *index,
		t_shell *shell, char *exp_input)
{
	char	*temp;
	char	*new_exp_input;

	temp = ft_extract_segment(input, index, shell);
	new_exp_input = ft_join_input(exp_input, temp);
	return (new_exp_input);
}

char	*ft_segment_helper_hd(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	start = *i;
	while (input[*i] != '\0' && input[*i] != '$' && input[*i] != '\"'
		&& input[*i] != '\'')
	{
		(*i)++;
	}
	end = *i;
	if (end > start)
	{
		segment = ft_extract_str(input, start, end);
		return (segment);
	}
	else
	{
		return (NULL);
	}
}

char	*extract_and_append_segment_hd(char *input, int *i, char *segment)
{
	char	*temp_segment;
	char	*new_segment;

	temp_segment = ft_segment_helper(input, i);
	if (temp_segment)
	{
		new_segment = ft_join_input(segment, temp_segment);
		return (new_segment);
	}
	return (segment);
}

char	*handle_and_append_variable_hd(char *input, int *i,
		char *segment, t_shell *shell)
{
	char	*exp_var;
	char	*expanded_var;
	char	*new_segment;

	if (input[*i] == '$')
	{
		exp_var = ft_extract_var(input, i);
		if (exp_var)
		{
			expanded_var = ft_expand_var_hd(shell, exp_var);
			if (expanded_var)
			{
				new_segment = ft_join_input(segment, expanded_var);
				return (new_segment);
			}
		}
	}
	return (segment);
}

char	*ft_extract_segment_hd(char *input, int *i, t_shell *shell)
{
	char	*segment;

	segment = ft_strdup("");
	if (!segment)
		return (NULL);
	while (input[*i] != '\0' && input[*i] != '\"' && input[*i] != '\'')
	{
		segment = extract_and_append_segment_hd(input, i, segment);
		segment = handle_and_append_variable_hd(input, i, segment, shell);
	}
	return (segment);
}
