#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "./minishell.h"

char	*ft_expander_heredoc(char *input, t_shell *shell);
char	*ft_extract_hered_dq(char *input, int *i, t_shell *shell);
char	*ft_expand_hered(t_shell *shell, char *var);
char	*ft_expand_hered_dq(t_shell *shell, char *var);

char	*ft_append_newline(char *str);
int		ft_open_file(char *filename, char *content, t_shell *shell);
char	*ft_heredoc_join(char *s1, char *s2);
int		ft_count_delimiters(t_token *tokens);
char	**ft_extract_delimiters(t_token *tokens);
int		ft_heredoc_check(t_shell *shell);

#endif
