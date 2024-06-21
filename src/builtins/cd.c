#include "../../includes/builtins.h"

// Updates the PWD and OLDPWD environment variables
int update_pwd(t_env_var **env_list, char *old_pwd)
{
    char buffer[1024];
    char *new_pwd;

    // Get the current working directory and store it in buffer
    new_pwd = getcwd(buffer, sizeof(buffer));
    if (!new_pwd) // Check if getcwd failed
    {
        perror("getcwd"); // Print error message
        return 1; // Return exit code 1 on error
    }
    // Update the OLDPWD environment variable to the old_pwd value
    update_env_var(env_list, "OLDPWD", old_pwd);
    // Update the PWD environment variable to the new_pwd value
    update_env_var(env_list, "PWD", new_pwd);

    return 0; // Return 0 on success
}

// Changes the directory to the home directory
int change_to_home(t_env_var **env_list)
{
    char *home_dir;

    // Retrieve the value of the HOME environment variable
    home_dir = get_env_value(*env_list, "HOME");
    if (!home_dir) // Check if HOME is not set
    {
        ft_putendl_fd("cd: HOME not set", STDERR_FILENO); // Print error message to stderr
        return 1; // Return exit code 1 on error
    }
    // Change directory to the home directory
    if (chdir(home_dir) != 0)
    {
        perror("chdir"); // Print error message if chdir fails
        return 1; // Return exit code 1 on error
    }

    return 0; // Return 0 on success
}

// Changes the current working directory
// Changes the current working directory
int ft_cd(char **args, t_env_var **env_list)
{
    char buffer[1024];
    char *old_pwd;
    int status;

    // Get the current working directory and store it in buffer
    old_pwd = getcwd(buffer, sizeof(buffer));
    if (!old_pwd) // Check if getcwd failed
    {
        perror("getcwd"); // Print error message
        return 1; // Return exit code 1 on error
    }

    // Check if no argument is given or the argument is '~'
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        // Change directory to the home directory
        status = change_to_home(env_list);
    }
    else if (chdir(args[1]) != 0) // Attempt to change directory to the given path
    {
        // Print the error message in the required format to stderr
        ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);

        return 1; // Return exit code 1 on error
    }
    else
    {
        status = 0; // Set status to 0 on success
    }

    // Update the PWD and OLDPWD environment variables
    if (status == 0) {
        status = update_pwd(env_list, old_pwd);
    }

    return status; // Return the final status
}

