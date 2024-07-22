/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dq_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:56:24 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/22 12:58:12 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/heredoc.h"

char	*ft_extract_segment_dq_hd(char *input, int *i)
{
	char	*segment;
	int		start;
	int		end;

	start = *i;
	while (input[*i] != '\0' && input[*i] != '$' && input[*i] != '\"')
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

char	*ft_handle_double_quote_hd(char *input, int *index,
		t_shell *shell, char *exp_input)
{
	char	*temp;
	char	*new_exp_input;

	temp = ft_extract_dq(input, index, shell);
	new_exp_input = ft_join_input(exp_input, temp);
	free(temp);
	return (new_exp_input);
}

char	*extract_and_append_segment_dq_hd(char *input, int *i, char *segment)
{
	char	*temp_segment;
	char	*new_segment;

	temp_segment = ft_extract_segment_dq(input, i);
	if (temp_segment)
	{
		new_segment = ft_join_input(segment, temp_segment);
		free(temp_segment);
		return (new_segment);
	}
	return (segment);
}

char	*handle_and_append_variable_dq_hd(char *input, int *i, char *segment,
		t_shell *shell)
{
	char	*exp_var;
	char	*expanded_var;
	char	*new_segment;

	if (input[*i] == '$')
	{
		exp_var = ft_extract_var(input, i);
		if (exp_var)
		{
			expanded_var = ft_expand_var_dq_hd(shell, exp_var);
			if (expanded_var)
			{
				new_segment = ft_join_input(segment, expanded_var);
				free(expanded_var);
				return (new_segment);
			}
			free(exp_var);
		}
	}
	return (segment);
}

char	*ft_extract_dq_hd(char *input, int *i, t_shell *shell)
{
	char	*segment;

	segment = strdup("");
	if (!segment)
		return (NULL);
	(*i)++;
	while (input[*i] != '\0' && input[*i] != '\"')
	{
		segment = extract_and_append_segment_dq_hd(input, i, segment);
		segment = handle_and_append_variable_dq_hd(input, i, segment, shell);
	}
	if (input[*i] == '\"')
		(*i)++;
	// segment = ft_quote_string(segment);
	return (segment);
}

// char	*ft_expand_var_dq_hd(t_shell *shell, char *var)
// {
// 	t_env	*current;
// 	char		*exp_var;

// 	if (ft_strcmp(var, "?") == 0)
// 		return (ft_itoa(shell->exit_code));
// 	if (ft_strcmp(var, " ") == 0 || ft_strcmp(var, "") == 0)
// 		return (ft_strdup("$"));
// 	current = shell->env_list;
// 	while (current != NULL)
// 	{
// 		if (ft_strcmp(current->key, var) == 0)
// 		{
// 			exp_var = current->value;
// 			free(var);
// 			return (ft_strdup(current->value));
// 		}

// 		current = current->next;
// 	}
// 	return (NULL);
// }
