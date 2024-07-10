#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>





// Function to handle the pwd command
// This function prints the current working directory
void	execute_pwd(void)
{
	char	buffer[1024];
	char	*cwd;

	cwd = getcwd(buffer, sizeof(buffer));
	if (cwd)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
		perror("getcwd");
}