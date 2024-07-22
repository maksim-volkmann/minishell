/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:57:08 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/22 12:58:12 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*ft_handle_segment(char *input, int *index, t_shell *shell,
		char *exp_input)
{
	char	*temp;
	char	*new_exp_input;

	temp = ft_extract_segment(input, index, shell);
	new_exp_input = ft_join_input(exp_input, temp);
	return (new_exp_input);
}

char	*ft_segment_helper(char *input, int *i)
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

char	*extract_and_append_segment(char *input, int *i, char *segment)
{
	char	*temp_segment;
	char	*new_segment;

	temp_segment = ft_segment_helper(input, i);
	if (temp_segment)
	{
		new_segment = ft_join_input(segment, temp_segment);
		// free(temp_segment);  // Free the temporary segment
		return (new_segment);
	}
	return (segment);
}

char	*handle_and_append_variable(char *input, int *i, char *segment,
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
			expanded_var = ft_expand_var(shell, exp_var);
			// free(exp_var);  // Free the extracted exp_var
			if (expanded_var)
			{
				new_segment = ft_join_input(segment, expanded_var);
				// free(expanded_var);  // Free the expanded_var
				return (new_segment);
			}
		}
	}
	return (segment);
}

char	*ft_extract_segment(char *input, int *i, t_shell *shell)
{
	char	*segment;

	segment = strdup("");
	if (!segment)
		return (NULL);
	while (input[*i] != '\0' && input[*i] != '\"' && input[*i] != '\'')
	{
		segment = extract_and_append_segment(input, i, segment);
		segment = handle_and_append_variable(input, i, segment, shell);
	}
	return (segment);
}

// char	*ft_expand_var(t_shell *shell, char *var)
// {
// 	t_env	*current;
// 	char		*exp_var;

// 	if (ft_strcmp(var, "?") == 0)
// 		return (ft_itoa(shell->exit_code));
// 	if (ft_strcmp(var, " ") == 0)
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

// char	*ft_extract_var(char *input, int *i)
// {
// 	int			j;
// 	char		*var;
// 	const int	var_len = ft_var_len(input, (*i));

// 	(*i)++;
// 	if (input[(*i)] == '?')
// 		return (ft_strdup("?") + ((*i)++, 0));
// 	if (input[(*i)] == ' ' || input[(*i)] == '\t' || input[(*i)] == '\0')
// 		return (ft_strdup(" "));
// 	var = malloc(var_len + 1);
// 	if (!var)
// 		return (NULL);
// 	j = 0;
// 	while (input[(*i)] && !ft_is_separator_var(input[(*i)]))
// 		var[j++] = input[(*i)++];
// 	var[j] = '\0';
// 	return (var);
// }

// char	*ft_extract_var(char *input, int *i)
// {
// 	char		*var;
// 	int			j;
// 	const int	var_len = ft_var_len(input, (*i));

// 	(*i)++;
// 	if (input[(*i)] == '?')
// 	{
// 		var = ft_strdup("?");
// 		(*i)++;
// 		return (var);
// 	}
// 	if (input[(*i)] == ' ' || input[(*i)] == '\t' || input[(*i)] == '\0')
// 		return (ft_strdup(" "));
// 	var = malloc(var_len + 1);
// 	j = 0;
// 	while (input[(*i)] != 0)
// 	{
// 		if (ft_is_separator_var(input[(*i)]) != 0)
// 			break ;
// 		else
// 		{
// 			var[j] = input[(*i)];
// 			j++;
// 			(*i)++;
// 		}
// 	}
// 	var[j] = '\0';
// 	return (var);
// }
