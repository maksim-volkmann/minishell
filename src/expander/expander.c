/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/27 15:55:11 by adrherna         ###   ########.fr       */
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

char	*ft_expander(char *input, t_shell *shell)
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
			temp = ft_extract_dq(input, &i, shell);
			exp_input = ft_join_input(exp_input, temp);
			free(temp);
		}
		else
		{
			temp = ft_extract_segment(input, &i, shell);
			exp_input = ft_join_input(exp_input, temp);
			free(temp);
		}
	}
	free(input);
	return (exp_input);
}

// char	*ft_extract_dq(char *input, int *i, t_env_var *env)
// {
// 	char	*segment;
// 	char	*exp_var;
// 	int		start;
// 	int		end;

// 	segment = ft_strdup("");
// 	while (input[(*i)] != 0 && input[(*i)] != '\"')
// 	{
// 		ft_extract_segment_dq(input, i);
// 		if (input[(*i)] == '$')
// 		{
// 			exp_var = ft_extract_var(input, i);
// 			exp_var = ft_expand_var(env, exp_var);
// 			if (exp_var != NULL)
// 				segment = ft_join_input(segment, exp_var);
// 			else
// 				segment = ft_join_input(segment, "");
// 		}
// 	}
// 	if (input[(*i)] == '\"')
// 		(*i)++;
// 	return (segment);
// }


// char	*ft_expander(char *input, t_env_var *env)
// {
// 	char	*exp_input;
// 	char	*exp_var;
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
// 		else if (input[i] == '$')
// 		{
// 			exp_var = ft_extract_var(input, &i);
// 			exp_var = ft_expand_var(env, exp_var);
// 			if (exp_var != NULL)
// 				exp_input = ft_join_input(exp_input, exp_var);
// 			else
// 				exp_input = ft_join_input(exp_input, "");
// 		}
// 		else
// 		{
// 			temp = ft_extract_segment(input, &i);
// 			exp_input = ft_join_input(exp_input, temp);
// 			free(temp);
// 		}
// 	}
// 	free(input);
// 	return (exp_input);
// }

			// exp_var = ft_extract_var(input, &i);
			// exp_var = ft_expand_var(env, exp_var);
			// temp = ft_strjoin(exp_input, exp_var);
			// free(exp_input);
			// exp_input = temp;

			// exp_var = ft_extract_var(input, &i);
			// exp_var = ft_expand_var(env, exp_var);
			// exp_input = ft_join_input(exp_input, exp_var);


// hola $USER
