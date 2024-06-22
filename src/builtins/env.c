#include "../../includes/builtins.h"
#include <unistd.h>

// Function to print error messages for invalid arguments
void print_env_error(char *arg)
{
    if (access(arg, F_OK) != 0)
    {
        ft_putstr_fd("env: ", STDERR_FILENO);
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
    }
    else if (access(arg, X_OK) != 0)
    {
        ft_putstr_fd("env: ", STDERR_FILENO);
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putendl_fd(": Permission denied", STDERR_FILENO);
    }
    else
    {
        ft_putstr_fd("env: ", STDERR_FILENO);
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putendl_fd(": Error", STDERR_FILENO);
    }
}

// Enhanced ft_env function to handle arguments and piping
int ft_env(char **args, t_shell *shell)
{
    int i = 1;

    // If there are arguments, handle errors
    if (args[1] != NULL)
    {
        while (args[i] != NULL)
        {
            print_env_error(args[i]);
            return 127; // Return non-zero exit code to indicate error
        }
    }
    else
    {
        // Check if there are pipes or redirections
        t_command *current = shell->cmds;
        while (current)
        {
            if (current->next != NULL || current->output != NULL)
            {
                print_env_vars(shell->env_list);
                return 0;
            }
            current = current->next;
        }
        // If no pipes or redirections, print all environment variables
        print_env_vars(shell->env_list);
    }
    return 0;
}
