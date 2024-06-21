#include "../../includes/builtins.h"

void ft_exit(char **args)
{
    int exit_status;

    exit_status = 0;
    if (args[1] && args[2])
    {
        ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
        exit_status = 1;
    }
    else if (args[1] && !ft_strisnum(args[1]))
    {
        ft_putstr_fd("exit: ", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putendl_fd(": numeric argument required", STDERR_FILENO);
        exit_status = 255;
    }
    else if (args[1])
    {
        exit_status = ft_atoi(args[1]);
    }
    exit(exit_status);
}
