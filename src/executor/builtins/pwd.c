#include "../../../includes/builtins.h"

void ft_pwd()
{
    char buffer[1024];
    char *cwd;

    cwd = getcwd(buffer, sizeof(buffer));
    if (cwd)
    {
        ft_putstr_fd(cwd, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
    else
    {
        perror("getcwd");
    }
}
