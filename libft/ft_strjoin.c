/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:03:33 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/16 11:09:13 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new_str != NULL)
	{
		while (*s1 != 0)
		{
			new_str[i] = *s1;
			s1++;
			i++;
		}
		while (*s2 != 0)
		{
			new_str[i] = *s2;
			s2++;
			i++;
		}
		new_str[i] = 0;
	}
	else
		return (NULL);
	return (new_str);
}

// int	main(void)
// {
// 	const char	*str1 = "";
// 	const char	*str2 = "";

// 	printf ("%s", ft_strjoin(str1, str2));
// 	return (0);
// }
