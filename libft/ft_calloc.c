/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:37:47 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/16 10:26:13 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (mem != NULL)
	{
		ft_memset(mem, 0, count * size);
	}
	return (mem);
}

// int	main(void)
// {
// 	int	*array;
// 	int	count;

// 	count = 6;
// 	array = ft_calloc(6, sizeof(int));
// 	while (count > 0)
// 	{
// 		printf ("%d", *array);
// 		array++;
// 		count--;
// 	}
// 	return (0);
// }
