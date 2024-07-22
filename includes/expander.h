# ifndef EXPANDER_H
# define EXPANDER_H

# include "./parser.h"
# include "./lexer.h"

// expander.c
char	*ft_expander(char *input, t_shell *shell);
char	*ft_extract_segment(char *input, int *i, t_shell *shell);
char	*ft_extract_sq(char *input, int *i);
char	*ft_extract_dq(char *input, int *i, t_shell *shell);

// helper.c
char	*ft_expand_var(t_shell *shell, char *var);
int		ft_is_separator_var(char c);
int		ft_var_len(char *token, int i);
char	*ft_extract_var(char *input, int *i);
char	*ft_join_input(char *s1, char *s2);

// helper_2.c

char	*ft_extract_segment_dq(char *input, int *i);
char	*ft_segment_helper(char *input, int *i);
char	*ft_quote_string(char *input);
char	*ft_strdup_dq(const char *s);
char	*ft_expand_var_dq(t_shell *shell, char *var);

// helper_3.c

char *ft_handle_single_quote(char *input, int *index, char *exp_input);

char *ft_handle_double_quote(char *input, int *index, t_shell *shell, char *exp_input);

char *ft_handle_segment(char *input, int *index, t_shell *shell, char *exp_input);

// // expander.c
// char	*ft_expander_hd(char *input, t_shell *shell);
// char	*ft_extract_segment_hd(char *input, int *i, t_shell *shell);
// char	*ft_extract_sq(char *input, int *i);
// char	*ft_extract_dq(char *input, int *i, t_shell *shell);

// // helper.c
// char	*ft_expand_var_hd(t_shell *shell, char *var);
// int		ft_is_separator_var_hd(char c);
// int		ft_var_len(char *token, int i);
// char	*ft_extract_var_hd(char *input, int *i);
// char	*ft_join_input_hd(char *s1, char *s2);

// // helper_2.c

// char	*ft_extract_segment_dq(char *input, int *i);
// char	*ft_segment_helper_hd(char *input, int *i);
// char	*ft_quote_string_hd(char *input);
// char	*ft_strdup_dq_hd(const char *s);
// char	*ft_expand_var_dq_hd(t_shell *shell, char *var);



// // helper_3.c

// char *ft_handle_single_quote(char *input, int *index, char *exp_input);

// char *ft_handle_double_quote_hd(char *input, int *index, t_shell *shell, char *exp_input);

// char *ft_handle_segment_hd(char *input, int *index, t_shell *shell, char *exp_input);

#endif

// wsl

// download ubuntu

// connect vs code to wsl