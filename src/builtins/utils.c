#include "../../includes/builtins.h"

int ft_strisnum(const char *str)
{
    int i;

    if (!str || !*str)
        return 0;
    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

char *get_env_value(t_env_var *env_list, const char *key)
{
    t_env_var *current = env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void add_env_var(t_env_var **env_list, const char *key, const char *value)
{
    t_env_var *new_var;
    t_env_var *current;
    t_env_var *prev;

    new_var = malloc(sizeof(t_env_var));
    if (!new_var)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_var->key = ft_strdup(key);
    new_var->value = ft_strdup(value);
    new_var->next = NULL;

    if (*env_list == NULL || ft_strcmp((*env_list)->key, key) > 0)
    {
        new_var->next = *env_list;
        *env_list = new_var;
    }
    else
    {
        current = *env_list;
        while (current != NULL && ft_strcmp(current->key, key) < 0)
        {
            prev = current;
            current = current->next;
        }
        prev->next = new_var;
        new_var->next = current;
    }
}

void update_env_var(t_env_var **env_list, const char *key, const char *value)
{
    t_env_var *current = *env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    add_env_var(env_list, key, value);
}

void print_env_vars(t_env_var *env_list)
{
    t_env_var *current;

    current = env_list;
    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}
