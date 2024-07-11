#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "./minishell.h"

char	*ft_expander_heredoc(char *input, t_shell *shell);
char	*ft_extract_hered_dq(char *input, int *i, t_shell *shell);
char	*ft_expand_hered(t_shell *shell, char *var);
char	*ft_expand_hered_dq(t_shell *shell, char *var);

int ft_open_file(char *filename, char *content, t_shell *shell);

#endif
