/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goldman <goldman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:49:37 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/09 17:32:48 by goldman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

char	*ft_expand_hered_dq(t_shell *shell, char *var)
{
	t_env_var	*current;
	// char		*exp_var;

	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(shell->exit_code));
	if (ft_strcmp(var, " ") == 0 || ft_strcmp(var, "") == 0)
		return (ft_strdup("$"));
	current = shell->env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			// exp_var = current->value;
			free(var);
			return (ft_strdup(current->value));
		}

		current = current->next;
	}
	return (NULL);
}

char	*ft_expand_var_hered(t_shell *shell, char *var)
{
	t_env_var	*current;
	// char		*exp_var;

	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(shell->exit_code));
	if (ft_strcmp(var, " ") == 0)
		return (ft_strdup("$"));
	current = shell->env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			// exp_var = current->value;
			free(var);
			return (ft_strdup(current->value));
		}

		current = current->next;
	}
	return (NULL);
}

char	*ft_extract_hered_dq(char *input, int *i, t_shell *shell)
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
				exp_var = ft_expand_hered_dq(shell, exp_var);
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

char	*ft_extract_segment_heredoc(char *input, int *i, t_shell *shell)
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
				exp_var = ft_expand_var_hered(shell, exp_var);
				if (exp_var)
					segment = ft_join_input(segment, exp_var);
				free(exp_var);
			}
		}
	}
	return (segment);
}

char	*ft_expander_heredoc(char *input, t_shell *shell)
{
	char	*exp_input;
	char	*temp;
	int		i;

	i = 0;
	exp_input = ft_strdup("");
	while (input[i] != 0)
	{
		if (input[i] == '\'')
		{
			temp = ft_extract_sq(input, &i);
			exp_input = ft_join_input(exp_input, temp);
			free(temp);
		}
		else if (input[i] == '\"')
		{
			temp = ft_extract_hered_dq(input, &i, shell);
			exp_input = ft_join_input(exp_input, temp);
			free(temp);
		}
		else
		{
			temp = ft_extract_segment_heredoc(input, &i, shell);
			exp_input = ft_join_input(exp_input, temp);
			free(temp);
		}
	}
	free(input);
	return (exp_input);
}
