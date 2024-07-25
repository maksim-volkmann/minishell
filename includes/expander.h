/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:24:02 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/25 18:11:02 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "./parser.h"

// double_quote.c
char	*ft_extract_segment_dq(char *input, int *i);
char	*ft_handle_double_quote(char *input, int *index,
			t_shell *shell, char *exp_input);
char	*extract_and_append_segment_dq(char *input, int *i, char *segment);
char	*handle_and_append_variable_dq(char *input, int *i, char *segment,
			t_shell *shell);
char	*ft_extract_dq(char *input, int *i, t_shell *shell);

// expander.c
char	*ft_expander(char *input, t_shell *shell);

// helper_2.c
char	*ft_expand_var(t_shell *shell, char *var);
char	*ft_extract_var(char *input, int *i);
char	*ft_expand_var_dq(t_shell *shell, char *var);

// helper.c
int		ft_var_len(char *input, int i);
char	*ft_join_input(char *s1, char *s2);
int		ft_is_separator_var(char c);
char	*ft_strdup_dq(const char *s);
char	*ft_quote_string(char *input);

// segment.c
char	*ft_handle_segment(char *input, int *index, t_shell *shell,
			char *exp_input);
char	*ft_segment_helper(char *input, int *i);
char	*extract_and_append_segment(char *input, int *i, char *segment);
char	*handle_and_append_variable(char *input, int *i, char *segment,
			t_shell *shell);
char	*ft_extract_segment(char *input, int *i, t_shell *shell);

// single_quote.c
char	*ft_handle_single_quote(char *input, int *index, char *exp_input);
char	*ft_extract_sq(char *input, int *i);

#endif
