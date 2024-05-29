/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:42:47 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/17 11:56:43 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;
	const char	*i;
	int			counter;

	counter = 0;
	str = s;
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			i = str;
			counter++;
		}
		str++;
	}
	if ((char)c == 0)
		return ((char *)str);
	else if (counter != 0)
		return ((char *)i);
	else
		return ((char *) NULL);
}

// int	main(void)
// {
// 	const char	*str1 = "hola que haces";
// 	const char	*str2 = "hola que haces";

// 	printf ("%s\n", strrchr(str1, 'z'));
// 	printf ("%s\n", ft_strrchr(str2, 'z'));
// 	return (0);
// }
