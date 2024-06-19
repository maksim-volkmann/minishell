#include "../../../includes/builtins.h"

void ft_unset(char **args, t_env_var **env_list)
{
    t_env_var *current;
    t_env_var *prev;
    int i;

    i = 1;
    while (args[i])
    {
        current = *env_list;
        prev = NULL;
        while (current)
        {
            if (ft_strcmp(current->key, args[i]) == 0)
            {
                if (prev == NULL)
                {
                    *env_list = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                free(current->key);
                free(current->value);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
}
