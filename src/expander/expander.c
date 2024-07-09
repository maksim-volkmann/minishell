/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/09 11:12:00 by adrherna         ###   ########.fr       */
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

// dq management

char *extract_and_append_segment_dq(char *input, int *i, char *segment)
{
	char *temp_segment = ft_extract_segment_dq(input, i);
	if (temp_segment)
	{
		char *new_segment = ft_join_input(segment, temp_segment);
		free(temp_segment);
		return new_segment;
	}
	return segment;
}

char *handle_and_append_variable_dq(char *input, int *i, char *segment, t_shell *shell)
{
	if (input[*i] == '$')
	{
		char *exp_var = ft_extract_var(input, i);
		if (exp_var)
		{
			char *expanded_var = ft_expand_var_dq(shell, exp_var);
			if (expanded_var)
			{
				char *new_segment = ft_join_input(segment, expanded_var);
				free(expanded_var);
				return new_segment;
			}
			free(exp_var);
		}
	}
	return segment;
}

char *ft_extract_dq(char *input, int *i, t_shell *shell)
{
	char *segment = strdup("");
	if (!segment)
		return NULL;

	(*i)++;
	while (input[*i] != '\0' && input[*i] != '\"')
	{

		segment = extract_and_append_segment_dq(input, i, segment);

		segment = handle_and_append_variable_dq(input, i, segment, shell);
	}
	if (input[*i] == '\"')
		(*i)++;
	segment = ft_quote_string(segment);
	return segment;
}

// char	*ft_extract_dq(char *input, int *i, t_shell *shell)
// {
// 	char	*segment;
// 	char	*exp_var;
// 	char	*temp_segment;

// 	segment = strdup("");
// 	if (!segment)
// 		return (NULL);
// 	(*i)++;
// 	while (input[*i] != '\0' && input[*i] != '\"')
// 	{
// 		temp_segment = ft_extract_segment_dq(input, i);
// 		// segment 1
// 		if (temp_segment)
// 		{
// 			segment = ft_join_input(segment, temp_segment);
// 			free(temp_segment);
// 		}
// 		//
// 		// segment 2
// 		if (input[*i] == '$')
// 		{
// 			exp_var = ft_extract_var(input, i);
// 			if (exp_var)
// 			{
// 				exp_var = ft_expand_var_dq(shell, exp_var);
// 				if (exp_var)
// 					segment = ft_join_input(segment, exp_var);
// 				free(exp_var);
// 			}
// 		}
// 		//
// 	}
// 	if (input[*i] == '\"')
// 		(*i)++;
// 	segment = ft_quote_string(segment);
// 	return (segment);
// }

// dq management

// segment management

char *extract_and_append_segment(char *input, int *i, char *segment)
{
	char *temp_segment;
	char *new_segment;

	temp_segment = ft_segment_helper(input, i);
	if (temp_segment)
	{
		new_segment = ft_join_input(segment, temp_segment);
		// free(temp_segment);  // Free the temporary segment
		return new_segment;
	}
	return segment;
}

char *handle_and_append_variable(char *input, int *i, char *segment, t_shell *shell)
{
	char *exp_var;
	char *expanded_var;
	char *new_segment;

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

char *ft_extract_segment(char *input, int *i, t_shell *shell)
{
	char *segment;

	segment = strdup("");
	if (!segment)
		return NULL;
	while (input[*i] != '\0' && input[*i] != '\"' && input[*i] != '\'')
	{
		segment = extract_and_append_segment(input, i, segment);
		segment = handle_and_append_variable(input, i, segment, shell);
	}
	return (segment);
}

// char	*ft_extract_segment(char *input, int *i, t_shell *shell)
// {
// 	char	*segment;
// 	char	*exp_var;
// 	char	*temp_segment;

// 	segment = strdup("");
// 	if (!segment)
// 		return (NULL);
// 	while (input[*i] != '\0' && input[*i] != '\"' && input[*i] != '\'')
// 	{
// 		temp_segment = ft_segment_helper(input, i);
// 		if (temp_segment)
// 		{
// 			segment = ft_join_input(segment, temp_segment);
// 			free(temp_segment);
// 		}
// 		if (input[*i] == '$')
// 		{
// 			exp_var = ft_extract_var(input, i);
// 			if (exp_var)
// 			{
// 				exp_var = ft_expand_var(shell, exp_var);
// 				if (exp_var)
// 					segment = ft_join_input(segment, exp_var);
// 				free(exp_var);
// 			}
// 		}
// 	}
// 	return (segment);
// }

// segment management

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
