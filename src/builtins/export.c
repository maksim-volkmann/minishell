// #include "../../includes/builtins.h"

// //TODO: '?' can't be the first char setting up new envs. Need to check for more cases.

// void ft_export(char **args, t_env_var **env_list)
// {
// 	int i;
// 	char *sep;
// 	char *key;
// 	char *value;

// 	if (args[1] == NULL)
// 	{
// 		print_env_vars(*env_list);
// 	}
// 	else
// 	{
// 		for (i = 1; args[i]; i++)
// 		{
// 			sep = ft_strchr(args[i], '=');
// 			if (sep)
// 			{
// 				key = ft_substr(args[i], 0, sep - args[i]);
// 				value = ft_strdup(sep + 1);
// 				update_env_var(env_list, key, value);
// 				free(key);
// 				free(value);
// 			}
// 			else
// 			{
// 				key = ft_strdup(args[i]);
// 				if (get_env_value(*env_list, key) == NULL)
// 				{
// 					add_env_var(env_list, key, "");
// 				}
// 				free(key);
// 			}
// 		}
// 	}
// }
