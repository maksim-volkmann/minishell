#include "../../includes/parser.h"
#include <stdlib.h>

void	assign_to_darray(char **src, char **darray, int *i, int *j)
{
	size_t const	len = ft_strlen(src[*i]) + 1;

	darray[*j] = (char *)malloc(len * sizeof(char));
	ft_strlcpy(darray[*j], src[*i], len);
	(*i)++;
	(*j)++;
}

void	ft_parser(t_shell *shell, t_token **tokens)
{
	t_token		*current;
	t_command	*new;

	current = *tokens;
	while (current != NULL)
	{
		if (current->type == PIPE)
			current = current->next;
		new = ft_new_node();
		new->argv = ft_get_darray(&current, &shell, new->input, new->output);
		// If no arguments, new->argv is already NULL
		add_or_init_node(&shell->cmds, new);
		// print_command(new);
	}
}
