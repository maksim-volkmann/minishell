// #include "../../includes/builtins.h"

// // The echo function
// void ft_echo(char **args, t_env_var *env_list)
// {
//     int i;
//     int newline;

//     (void)env_list; // Avoid unused parameter warning
//     newline = 1;
//     i = 1;
//     if (args[1] && ft_strcmp(args[1], "-n") == 0)
//     {
//         newline = 0;
//         i++;
//     }
//     while (args[i])
//     {
//         ft_putstr_fd(args[i], STDOUT_FILENO);
//         if (args[i + 1])
//             ft_putchar_fd(' ', STDOUT_FILENO);
//         i++;
//     }
//     if (newline)
//         ft_putchar_fd('\n', STDOUT_FILENO);
// }
