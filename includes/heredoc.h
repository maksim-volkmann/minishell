/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:53:31 by adrherna          #+#    #+#             */
/*   Updated: 2024/07/24 12:59:30 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef HEREDOC_H
# define HEREDOC_H

# include "./parser.h"
# include "./expander.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include <unistd.h>
# include <fcntl.h>

// expander.c
char	*ft_expander_hd(char *input, t_shell *shell);

// dq_heredoc.c

char	*ft_extract_segment_dq_hd(char *input, int *i);
char	*ft_handle_double_quote_hd(char *input, int *index,
			t_shell *shell, char *exp_input);
char	*extract_and_append_segment_dq_hd(char *input, int *i, char *segment);
char	*handle_and_append_variable_dq_hd(char *input, int *i, char *segment,
			t_shell *shell);
char	*ft_extract_dq_hd(char *input, int *i, t_shell *shell);

// helper.c

char	*ft_expand_var_dq_hd(t_shell *shell, char *var);
char	*ft_expand_var_hd(t_shell *shell, char *var);

// seg_heredoc.c

char	*ft_handle_segment_hd(char *input, int *index,
			t_shell *shell, char *exp_input);
char	*ft_segment_helper_hd(char *input, int *i);
char	*extract_and_append_segment_hd(char *input, int *i, char *segment);
char	*handle_and_append_variable_hd(char *input, int *i,
			char *segment, t_shell *shell);
char	*ft_extract_segment_hd(char *input, int *i, t_shell *shell);

#endif