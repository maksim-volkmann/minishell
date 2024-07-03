# ifndef EXPANDER_H
# define EXPANDER_H

# include "./parser.h"
# include "./lexer.h"

// expander.c
char	*ft_expander(char *input, t_shell *shell);
char	*ft_extract_segment(char *input, int *i, t_shell *shell);

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
char	*ft_expand_var_dq(t_shell *shell, char *var);
#endif
