/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:39:01 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/16 10:33:09 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*sus;
	size_t			i;

	sus = b;
	i = 0;
	while (i < len)
	{
		*sus = (unsigned char)c;
		sus++;
		i++;
	}
	return (b);
}

// int	main(void)
// {
// 	char str[] = "holaa";
// 	int i = 0;

// 	ft_memset(str, 0, sizeof(str));
// 	while (i < 5)
// 	{
// 		printf ("%d\n", str[i]);
// 		i++;
// 	}
// 	return (0);
// }
