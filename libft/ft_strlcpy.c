/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:39:50 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/21 15:31:46 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			expec_len;

	expec_len = ft_strlen(src);
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (dstsize == 0)
		return (expec_len);
	if (dstsize > 0 && dst && src)
	{
		while (dstsize > 1 && *s)
		{
			*(d++) = *(s++);
			dstsize--;
		}
	}
	*d = 0;
	return (expec_len);
}

// int main(void)
// {
// 	char dest1[10];
// 	char dest2[10];
// 	char src[] = "hola que haces";

// 	// strlcpy(dest1, src, 10);
// 	ft_strlcpy(dest2, src, 0);

// 	// printf("%s\n", dest1);
// 	printf("%s\n", dest2);
// 	return (0);
// }
