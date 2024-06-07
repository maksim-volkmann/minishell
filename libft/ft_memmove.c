/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:30:05 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/17 09:27:38 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	if (dst <= src)
	{
		while (len-- > 0)
			*(d++) = *(s++);
	}
	else
	{
		d += len;
		s += len;
		while (len-- > 0)
			*(--d) = *(--s);
	}
	return (dst);
}

// int	main(void)
// {
// 	char dest1[20];
// 	char dest2[20];
// 	char src[] = "Learningisfun";

// 	memmove(dest1, src, 10);
// 	ft_memmove(dest2, src, 10);
// 	printf("%s\n", dest1);
// 	printf("%s\n", dest2);
// 	return (0);
// }
