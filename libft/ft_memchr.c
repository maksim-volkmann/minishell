/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:40:21 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/17 09:35:27 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		d;

	str = (const unsigned char *)s;
	d = (unsigned char)c;
	while (n > 0)
	{
		if (*str == d)
		{
			return ((void *)str);
		}
		str++;
		n--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	*str = "hello how are you";

// 	printf ("%s", ft_memchr(str, 'o', 10));
// 	return (0);
// }
