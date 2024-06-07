/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:37:19 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/21 15:35:23 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*d;
	const unsigned char		*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	s = src;
	i = 0;
	while (i < n)
	{
		*d = *s;
		i++;
		d++;
		s++;
	}
	return (dst);
}

// int	main(void)
// {
// 	char dest[22];
// 	char src[] = "test basic du memcpy !";

// 	ft_memcpy(dest, src, sizeof(int), 22);
// 	memcpy(dest, src, sizeof(int), 22);
// }
