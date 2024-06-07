/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:02:53 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/17 09:50:12 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (n > 0)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
		n--;
	}
	return (0);
}

// int	main(void)
// {
// 	const int	arr1[] = {1, 2, 3, 4, 5};
// 	const int	arr2[] = {1, 2, 3, 4, 5};

// 	printf("%d\n", ft_memcmp(arr1, arr2, 12));
// 	printf("%d\n", memcmp(arr1, arr2, 12));
// }
